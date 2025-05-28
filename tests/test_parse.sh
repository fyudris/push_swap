#!/usr/bin/env bash

# Determine script and binary paths
dir="$(cd "$(dirname "$0")" && pwd)"
bin="$dir/../push_swap"

# ANSI color codes
GREEN="\033[32m"
RED="\033[31m"
BLUE="\033[34m"
RESET="\033[0m"

echo -e "${BLUE}Running parse tests...${RESET}"

test_case() {
    local type="$1"
    local input="$2"
    local expected_ret="$3"
    local expected_out="$4"

    printf "%bTest %-8s %bInput: '%s'%b\n" "${BLUE}" "$type" "${RESET}" "$input" "${RESET}"
    local output ret
    output=$("$bin" "$input" 2>/dev/null)
    ret=$?

    # Compare exit code
    if [ "$ret" -ne "$expected_ret" ]; then
        printf "%bFAIL%b: '%s' returned %d, expected %d\n" \
            "${RED}" "${RESET}" "$input" "$ret" "$expected_ret"
        exit 1
    fi

    # If we expect output, compare it
    if [ -n "$expected_out" ] && [ "$output" != "$expected_out" ]; then
        printf "%bFAIL%b: '%s' output:\n[Got]\n%s\n[Expected]\n%s\n" \
            "${RED}" "${RESET}" "$input" "$output" "$expected_out"
        exit 1
    fi

    printf "%bPASS%b: %s\n\n" "${GREEN}" "${RESET}" "$type"
}

# valid cases
test_case "Valid"   "4 3 2"       0 $'4\n3\n2'
test_case "Valid"   " 10   -5 7"  0 $'10\n-5\n7'
test_case "Valid"   "+123 -456 0" 0 $'123\n-456\n0'

# error cases
test_case "Empty"    ""             1 ""
test_case "Letters"  "a 1 2"        1 ""
test_case "SignOnly" "+ - 5"        1 ""
test_case "Overflow" "2147483648"   1 ""
test_case "Underflow" "-2147483649" 1 ""
test_case "Duplicate" "1 2 1"       1 ""
