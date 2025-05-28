#!/usr/bin/env bash
set -e

DIR="$(cd "$(dirname "$0")" && pwd)"
ROOT="${DIR}/.."

GREEN="\033[32m"
RED="\033[31m"
BLUE="\033[34m"
RESET="\033[0m"

echo -e "${BLUE}Running sort_three tests...${RESET}"

# Helper: test one 3-element permutation
run_test() {
    init=($1)
    driver_c="$DIR/driver_sort3_${init[*]// /_}.c"
    driver_ex="$DIR/driver_sort3_${init[*]// /_}"

    # Generate driver source
    cat > "$driver_c" << EOF
#include "push_swap.h"
#include <unistd.h>
int main(void) {
    t_stack_node *a = NULL;
    char *nums[] = {"${init[0]}", "${init[1]}", "${init[2]}", NULL};
    init_stack(&a, nums);
    sort_three(&a);
    while (a) {
        ft_putnbr_fd(a->value, 1);
        if (a->next) write(1, " ", 1);
        a = a->next;
    }
    write(1, "\n", 1);
    free_stack(&a);
    return 0;
}
EOF

    # Compile driver (no‐PIE to silence warnings)
    gcc -Wall -Wextra -Werror \
        -I"$ROOT/includes" -I"$ROOT/libft/includes" \
        "$ROOT/src/push_swap/init_stack.c" \
        "$ROOT/src/push_swap/parse_args.c" \
        "$ROOT/src/operations/swap.c" \
        "$ROOT/src/operations/rotate.c" \
        "$ROOT/src/operations/reverse_rotate.c" \
        "$ROOT/src/operations/sort_three.c" \
        "$driver_c" \
        -L"$ROOT/libft" -lft -no-pie \
        -o "$driver_ex"

    # Run and capture all output, then extract only the last line
    raw_out="$("$driver_ex")"
    out="$(printf "%s\n" "$raw_out" | tail -n1)"

    # Cleanup
    rm -f "$driver_ex" "$driver_c"

    # Compare to expected
    if [ "$out" = "1 2 3" ]; then
        echo -e "${GREEN}PASS${RESET}: sort_three ${init[*]} → $out"
    else
        echo -e "${RED}FAIL${RESET}: sort_three ${init[*]} → got '$out', expected '1 2 3'"
        exit 1
    fi
}

# Test all 6 permutations
run_test "1 2 3"
run_test "2 1 3"
run_test "3 2 1"
run_test "3 1 2"
run_test "1 3 2"
run_test "2 3 1"

echo -e "${BLUE}All sort_three tests passed.${RESET}"
