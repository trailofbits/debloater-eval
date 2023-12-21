#!/bin/bash

ORIGIN_BIN=./uniq.origin
REDUCED_BIN=./src/uniq
LOG=log.txt

# $1: option
function desired_run() {
  temp1=$({  $REDUCED_BIN $1 data.txt; } 2>&1 || exit 1)
  temp2=$({ $ORIGIN_BIN $1 data.txt; } 2>&1)
  diff -q <(echo $temp1) <(echo $temp2) >&/dev/null || exit 1
  temp1=$({  $REDUCED_BIN $1 input; } 2>&1 || exit 1)
  temp2=$({ $ORIGIN_BIN $1 input; })
  diff -q <(echo $temp1) <(echo $temp2) >&/dev/null || exit 1
  return 0
}

desired_run "" || exit 1
desired_run "-c" || exit 1
desired_run "-d" || exit 1
desired_run "-u" || exit 1
desired_run "-i" || exit 1
desired_run "-f 5" || exit 1
desired_run "-s 10" || exit 1
desired_run "-w 10" || exit 1

# --help and no args
function output_and_return_test() {
  TRIMMED_REDUCED_BIN=${REDUCED_BIN##* }
  ORIGIN_OUTPUT=$($ORIGIN_BIN "$@" < /dev/null 2>&1 | sed "s@$ORIGIN_BIN@@")
  ORIGIN_OUTPUT=$(echo "$ORIGIN_OUTPUT" | sed "s@$(basename $ORIGIN_BIN)@@")
  ORIGIN_OUTPUT=$(echo "$ORIGIN_OUTPUT" | sed "s@$uniq@@")    
  REDUCED_OUTPUT=$($REDUCED_BIN "$@" < /dev/null 2>&1 | sed "s@$TRIMMED_REDUCED_BIN@@")
  REDUCED_OUTPUT=$(echo "$REDUCED_OUTPUT" | sed "s@$(basename $TRIMMED_REDUCED_BIN)@@")
  REDUCED_OUTPUT=$(echo "$REDUCED_OUTPUT" | sed "s@$uniq@@")  
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
11;rgb:3030/0a0a/2424
