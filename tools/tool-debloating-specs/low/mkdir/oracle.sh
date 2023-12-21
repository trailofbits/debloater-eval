#!/bin/bash

ORIGIN_BIN=./mkdir.origin
REDUCED_BIN=./src/mkdir
LOG=log.txt

function run() {
  rm -rf d1
  { $REDUCED_BIN $1 $2; } >&$LOG || exit 1
  temp1=$(ls -ald $2 2>/dev/null | cut -d ' ' -f 1,2,3,4)
  rm -rf d1 >&/dev/null
  /bin/mkdir $1 $2
  temp2=$(ls -ald $2 2>/dev/null | cut -d ' ' -f 1,2,3,4)
  rm -rf $2 >&/dev/null
  if [[ $temp1 == $temp2 ]]; then
    return 0
  else
    return 1
  fi
}

function run_error() {
  rm -rf d1 >&/dev/null
  { $REDUCED_BIN $1 $2; } >&temp1 && exit 1
  rm -rf d1 >&/dev/null
  { $ORIGIN_BIN $1 $2; } >&temp2
  temp1=$(head -n 1 temp1 | cut -d ' ' -f 2,3)
  temp2=$(head -n 1 temp2 | cut -d ' ' -f 2,3)
  if [[ $temp1 == $temp2 ]]; then
    return 0
  else
    return 1
  fi
}

run "" d1 || exit 1
run_error "" d1/d2 || exit 1
run_error "-m 123124" d1/d2 || exit 1
run_error "-m" d1/d2 || exit 1
run "-m 400" d1 || exit 1
run "-m 555" d1 || exit 1
run "-m 644" d1 || exit 1
run "-m 610" d1 || exit 1
run "-m 777" d1 || exit 1
run "-p" d1/d2 || exit 1
rm -rf d1
run "-p" d1/d2/d3/d4 || exit 1
rm -rf d1
/bin/mkdir d1
run "-p" d1 || exit 1
rm -rf d1
/bin/mkdir d1
run "-p" d1/d2 || exit 1
rm -rf d1

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
