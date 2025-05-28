#!/usr/bin/env bash
set -e

# locate project root and binaries
DIR="$(cd "$(dirname "$0")" && pwd)"
ROOT="$DIR/.."
BIN="$ROOT/push_swap"
CHECKER="$ROOT/checker_linux"

# ensure the executables exist
if [ ! -x "$BIN" ]; then
  echo "Error: '$BIN' not found. Run 'make' in project root first." >&2
  exit 1
fi
if [ ! -x "$CHECKER" ]; then
  echo "Error: '$CHECKER' not found. Ensure your checker_linux is in the project root." >&2
  exit 1
fi

# a small test
ARGS="3 2 5 1 4"
OUT="$("$BIN" $ARGS)"

# feed our output into the checker
echo "$OUT" | "$CHECKER" $ARGS

# report how many moves it took
echo "Sorted in $(printf "%s\n" "$OUT" | wc -l) moves."
