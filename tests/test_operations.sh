#!/usr/bin/env bash
set -e

# Directories
DIR="$(cd "$(dirname "$0")" && pwd)"
ROOT="${DIR}/.."

# Colors
GREEN="\033[32m"
RED="\033[31m"
BLUE="\033[34m"
RESET="\033[0m"

echo -e "${BLUE}Running operation tests...${RESET}"

# Helper: generate, compile, and run a driver for a given op
# Usage: run_test <op> <initA> <initB> <expectedA> <expectedB>
run_test() {
    opname="$1"; shift
    initA=($1); shift
    initB=($1); shift
    expectedA="$1"; shift
    expectedB="$1"

    driver_c="$DIR/driver_${opname}.c"
    driver_ex="$DIR/driver_${opname}"

    # Generate driver source
    cat > "$driver_c" << EOF
#include "push_swap.h"
#include <unistd.h>
int main(void) {
    t_stack_node *a = NULL, *b = NULL;
    {
        char *nums[] = {
EOF
    for v in "${initA[@]}"; do
        printf '            "%s",\n' "$v" >> "$driver_c"
    done
    cat >> "$driver_c" << EOF
            NULL
        };
        init_stack(&a, nums);
    }
    {
        char *nums[] = {
EOF
    for v in "${initB[@]}"; do
        printf '            "%s",\n' "$v" >> "$driver_c"
    done
    cat >> "$driver_c" << EOF
            NULL
        };
        init_stack(&b, nums);
    }
EOF

    # Invoke the operation on the correct stack(s)
    case "$opname" in
        sa|ra|rra)
            printf '    %s(&a, false);\n' "$opname" >> "$driver_c" ;;
        sb|rb|rrb)
            printf '    %s(&b, false);\n' "$opname" >> "$driver_c" ;;
        ss|rr|rrr)
            printf '    %s(&a, &b, false);\n' "$opname" >> "$driver_c" ;;
        pa)
            printf '    %s(&a, &b, false);\n' "$opname" >> "$driver_c" ;;
        pb)
            printf '    %s(&b, &a, false);\n' "$opname" >> "$driver_c" ;;
    esac

    # Dump stacks
    cat >> "$driver_c" << 'EOF'
    // Dump stack a
    while (a) {
        ft_putnbr_fd(a->value, 1);
        if (a->next) write(1, " ", 1);
        a = a->next;
    }
    write(1, "\n", 1);
    // Dump stack b
    while (b) {
        ft_putnbr_fd(b->value, 1);
        if (b->next) write(1, " ", 1);
        b = b->next;
    }
    write(1, "\n", 1);
    free_stack(&a);
    free_stack(&b);
    return 0;
}
EOF

    # Determine source files needed
    srcs=(
        "$ROOT/src/push_swap/init_stack.c"
        "$ROOT/src/push_swap/parse_args.c"
    )
    case "$opname" in
        sa|sb|ss)    srcs+=("$ROOT/src/operations/swap.c") ;;
        pa|pb)       srcs+=("$ROOT/src/operations/push.c") ;;
        ra|rb|rr)    srcs+=("$ROOT/src/operations/rotate.c") ;;
        rra|rrb|rrr) srcs+=("$ROOT/src/operations/reverse_rotate.c") ;;
    esac

    # Compile
    cc -Wall -Wextra -Werror \
        -I"$ROOT/includes" -I"$ROOT/libft/includes" \
        "${srcs[@]}" \
        "$driver_c" \
        -L"$ROOT/libft" -lft \
        -o "$driver_ex"

    # Run and capture
    out=$("$driver_ex")

    # Cleanup
    rm "$driver_ex" "$driver_c"

    actualA="$(printf "%s" "$out" | sed -n '1p')"
    actualB="$(printf "%s" "$out" | sed -n '2p')"

    if [ "$actualA" = "$expectedA" ] && [ "$actualB" = "$expectedB" ]; then
        echo -e "${GREEN}PASS${RESET}: $opname → a: '$actualA' | b: '$actualB'"
    else
        echo -e "${RED}FAIL${RESET}: $opname"
        echo "  got   a: '$actualA' | b: '$actualB'"
        echo "  expect a: '$expectedA' | b: '$expectedB'"
        exit 1
    fi
}

# Tests
run_test sa  "2 1 3" ""      "1 2 3"    ""
run_test sb  ""      "2 1 3"  ""         "1 2 3"
run_test ss  "2 1"  "4 3"    "1 2"      "3 4"
run_test pa  ""      "1 2"    "1"        "2"
run_test pb  "1 2"   ""       "2"        "1"
run_test ra  "1 2 3" ""       "2 3 1"    ""
run_test rb  ""      "1 2 3"  ""         "2 3 1"
run_test rr  "1 2"   "3 4"    "2 1"      "4 3"
run_test rra "1 2 3" ""       "3 1 2"    ""
run_test rrb ""      "1 2 3"  ""         "3 1 2"
run_test rrr "1 2"   "3 4"    "2 1"      "4 3"

echo -e "${BLUE}All operation tests passed.${RESET}"
