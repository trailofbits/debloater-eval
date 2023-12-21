#!/bin/bash

ORIGIN_BIN=./gzip.origin
REDUCED_BIN=./gzip
LOG=log.txt


function crash() {
  retval=$1
  log=$2
  # crash detected by shell
  if [[ $retval -eq 124 ]]; then # timeout
    return 0
  elif [[ $retval -gt 128 ]]; then
    return 0
  fi
  # crash detected by sanitizer
  echo $log | grep "Sanitizer" >&/dev/null && return 0
  return 1
}


# -c
$ORIGIN_BIN -c <references/sample1.ref >sample1.gz 2>/dev/null
{  $REDUCED_BIN -c <references/sample1.ref >sample1.rb2; } 2>$LOG
crash $? && exit 1
cmp sample1.gz sample1.rb2 >&/dev/null || exit 1
# -d
{  $REDUCED_BIN -d <sample1.gz >sample1.tst; } 2>$LOG
crash $? && exit 1
cmp sample1.tst references/sample1.ref >&/dev/null || exit 1
# -f
echo "1234" >foo
$ORIGIN_BIN -c foo >&/dev/null
{  $REDUCED_BIN -f foo; } 2>$LOG
crash $? && exit 1
# -t (expected to return 1)
echo "1234" >foo
{  $REDUCED_BIN -t foo; } 2>$LOG
if [[ $? -ne 1 ]]; then
  exit 1
fi
# -t
{  $REDUCED_BIN -t sample1.gz; } 2>$LOG
crash $? && exit 1

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
