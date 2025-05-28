#!/usr/bin/env bash

# Determine script and binary paths
dir="$(cd "$(dirname "$0")" && pwd)"
bin="$dir/../push_swap"

# ANSI color codes
GREEN="\033[32m"
RED="\033[31m"
BLUE="\033[34m"
RESET="\033[0m"

echo -e "${BLUE}Running init tests...${RESET}"

run_single() {
    input="$1"
    expected_ret=$2
    expected_out="$3"

    printf "%b[Single] Input: '%s'%b\n" "${BLUE}" "$input" "${RESET}"
    output=$("$bin" "$input" 2>/dev/null)
    ret=$?

    if [ $ret -ne $expected_ret ]; then
        printf "%bFAIL%b: returned %d, expected %d\n" "${RED}" "${RESET}" $ret $expected_ret
        exit 1
    fi
    if [ "$expected_out" != "" ] && [ "$output" != "$expected_out" ]; then
        printf "%bFAIL%b: got:\n%s\nexpected:\n%s\n" "${RED}" "${RESET}" "$output" "$expected_out"
        exit 1
    fi
    printf "%bPASS%b\n\n" "${GREEN}" "${RESET}"
}

run_multi() {
    expected_ret=$1
    expected_out="$2"
    shift 2
    args=($@)

    printf "%b[Multi ] Input: %s%b\n" "${BLUE}" "${args[*]}" "${RESET}"
    output=$("$bin" "${args[@]}" 2>/dev/null)
    ret=$?

    if [ $ret -ne $expected_ret ]; then
        printf "%bFAIL%b: returned %d, expected %d\n" "${RED}" "${RESET}" $ret $expected_ret
        exit 1
    fi
    if [ "$expected_out" != "" ] && [ "$output" != "$expected_out" ]; then
        printf "%bFAIL%b: got:\n%s\nexpected:\n%s\n" "${RED}" "${RESET}" "$output" "$expected_out"
        exit 1
    fi
    printf "%bPASS%b\n\n" "${GREEN}" "${RESET}"
}

# Valid cases
run_single "4 3 2" 0 $'4
3
2'
run_multi 0 $'4
3
2' 4 3 2

run_single " 10   -5 7" 0 $'10
-5
7'
run_multi 0 $'10
-5
7' 10 -5 7

# Error cases
run_single "" 1 ""
run_multi 1 ""     # no args → returns 1
run_single "a 1 2" 1 ""
run_multi 1 "" a 1 2
run_single "1 2 1" 1 ""
run_multi 1 "" 1 2 1
run_single "2147483648" 1 ""
run_multi 1 "" 2147483648
