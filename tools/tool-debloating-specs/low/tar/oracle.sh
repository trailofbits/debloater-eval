#!/bin/bash
REDUCED_BIN=./src/tar
ORIGIN_BIN=./tar.origin
LOG=log.txt

cp ./tar.orig tar
for file in $(ls tests/tar*); do
  { sh -e $file; } >&$LOG || exit 1
  rm -rf f* b*
done

# --help and no args
function output_and_return_test() {
  TRIMMED_REDUCED_BIN=${REDUCED_BIN##* }
  ORIGIN_OUTPUT=$($ORIGIN_BIN "$@" < /dev/null 2>&1 | sed "s@$ORIGIN_BIN@@")
  ORIGIN_OUTPUT=$(echo "$ORIGIN_OUTPUT" | sed "s@$(basename $ORIGIN_BIN)@@")
  REDUCED_OUTPUT=$($REDUCED_BIN "$@" < /dev/null 2>&1 | sed "s@$TRIMMED_REDUCED_BIN@@")
  REDUCED_OUTPUT=$(echo "$REDUCED_OUTPUT" | sed "s@$(basename $TRIMMED_REDUCED_BIN)@@")
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
