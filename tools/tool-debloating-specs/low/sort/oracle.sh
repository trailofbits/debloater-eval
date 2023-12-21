#!/bin/bash

REDUCED_BIN=./src/sort
ORIGIN_BIN=./sort.origin
LOG=log.txt

function run() {
  $REDUCED_BIN $1 $input >&$LOG || exit 1
  $ORIGIN_BIN $1 $input >&temp2
  diff -q $LOG temp2 || exit 1
}

for input in $(ls input/*); do
  run "" || exit 1
  run "-r" || exit 1
  run "-s" || exit 1
  run "-u" || exit 1
  run "-z" || exit 1
done


# --help and no args
function output_and_return_test() {
  TRIMMED_REDUCED_BIN=${REDUCED_BIN##* }
  ORIGIN_OUTPUT=$($ORIGIN_BIN "$@" < /dev/null 2>&1 | sed "s@$ORIGIN_BIN@@")
  ORIGIN_OUTPUT=$(echo "$ORIGIN_OUTPUT" | sed -e "s@$(basename $ORIGIN_BIN)@@" -e "s@$(basename $TRIMMED_REDUCED_BIN)@@")
  REDUCED_OUTPUT=$($REDUCED_BIN "$@" < /dev/null 2>&1 | sed "s@$TRIMMED_REDUCED_BIN@@")
  REDUCED_OUTPUT=$(echo "$REDUCED_OUTPUT" | sed -e "s@$(basename $ORIGIN_BIN)@@" -e "s@$(basename $TRIMMED_REDUCED_BIN)@@")
  [[ "$ORIGIN_OUTPUT" = "$REDUCED_OUTPUT" ]] || return 1
  $ORIGIN_BIN "$@" < /dev/null 2>&1 >/dev/null
  ORIGIN_EXIT_CODE=$?
  $REDUCED_BIN "$@" < /dev/null 2>&1 >/dev/null
  REDUCED_EXIT_CODE=$?
  [[ $ORIGIN_EXIT_CODE == $REDUCED_EXIT_CODE ]] || return 1
  return 0
}

output_and_return_test --help || exit 1
output_and_return_test  || exit 1

exit 0

