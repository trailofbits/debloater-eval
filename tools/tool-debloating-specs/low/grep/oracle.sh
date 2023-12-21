#!/bin/bash

REDUCED_BIN=./src/grep
ORIGIN_BIN=./grep.origin
LOG=log.txt

{  $REDUCED_BIN "a" input2; } >&$LOG || exit 1
$ORIGIN_BIN "a" input2 >&log2
diff -q $LOG log2 >&/dev/null || exit 1

{  $REDUCED_BIN "a" -v -H -r input_dir; } >&$LOG || exit 1
{  $ORIGIN_BIN "a" -v -H -r input_dir; } >&log2
diff -q $LOG log2 >&/dev/null || exit 1

{  $REDUCED_BIN "1" -h -r input_dir; } >&$LOG || exit 1
{  $ORIGIN_BIN "1" -h -r input_dir; } >&log2
diff -q $LOG log2 >&/dev/null || exit 1

{  $REDUCED_BIN -n "si" input2; } >&$LOG || exit 1
{  $ORIGIN_BIN -n "si" input2; } >&log2
diff -q $LOG log2 >&/dev/null || exit 1

{  $REDUCED_BIN "1" -r input_dir -l; } >&$LOG || exit 1
{  $ORIGIN_BIN "1" -r input_dir -l; } >&log2
diff -q $LOG log2 >&/dev/null || exit 1

{  $REDUCED_BIN "1" -r input_dir -L; } >&$LOG || exit 1
{  $ORIGIN_BIN "1" -r input_dir -L; } >&log2
diff -q $LOG log2 >&/dev/null || exit 1

{  $REDUCED_BIN "randomtext" -r input_dir -c; } >&$LOG || exit 1
{  $ORIGIN_BIN "randomtext" -r input_dir -c; } >&log2
diff -q $LOG log2 >&/dev/null || exit 1

{  $REDUCED_BIN -o [r][a][n][d]* input2; } >&$LOG || exit 1
{  $ORIGIN_BIN -o [r][a][n][d]* input2; } >&log2
diff -q $LOG log2 >&/dev/null || exit 1

{  $REDUCED_BIN "1" -r input_dir -q; } >&$LOG || exit 1
{  $ORIGIN_BIN "1" -r input_dir -q; } >&log2
diff -q $LOG log2 >&/dev/null || exit 1

{  $REDUCED_BIN "1" -r input_dir -s; } >&$LOG || exit 1
{  $ORIGIN_BIN "1" -r input_dir -s; } >&log2
diff -q $LOG log2 >&/dev/null || exit 1

{  $REDUCED_BIN -v "a" input2; } >&$LOG || exit 1
{  $ORIGIN_BIN -v "a" input2; } >&log2
diff -q $LOG log2 >&/dev/null || exit 1

{  $REDUCED_BIN -i "Si" input2; } >&$LOG || exit 1
{  $ORIGIN_BIN -i "Si" input2; } >&log2
diff -q $LOG log2 >&/dev/null || exit 1

{  $REDUCED_BIN -w "Si" input2; } >&$LOG || exit 1
{  $ORIGIN_BIN -w "Si" input2; } >&log2
diff -q $LOG log2 >&/dev/null || exit 1

{  $REDUCED_BIN -x "Don't" input2; } >&$LOG || exit 1
{  $ORIGIN_BIN -x "Don't" input2; } >&log2
diff -q $LOG log2 >&/dev/null || exit 1

{  $REDUCED_BIN -F "randomtext*" input2; } >&$LOG || exit 1
{  $ORIGIN_BIN -F "randomtext*" input2; } >&log2
diff -q $LOG log2 >&/dev/null || exit 1

{  $REDUCED_BIN -E "randomtext*" input2; } >&$LOG || exit 1
{  $ORIGIN_BIN -E "randomtext*" input2; } >&log2
diff -q $LOG log2 >&/dev/null || exit 1

{  $REDUCED_BIN "ye " input; } >&$LOG || exit 1
{  $ORIGIN_BIN "ye " input; } >&log2
diff -q $LOG log2 >&/dev/null || exit 1

{  $REDUCED_BIN "cold" input; } >&$LOG || exit 1
{  $ORIGIN_BIN "cold" input; } >&log2
diff -q $LOG log2 >&/dev/null || exit 1

{  $REDUCED_BIN "not exist" input; } >&$LOG
{  $ORIGIN_BIN "not exist" input; } >&log2
diff -q $LOG log2 >&/dev/null || exit 1

{  $REDUCED_BIN ^D input2; } >&$LOG || exit 1
{  $ORIGIN_BIN ^D input2; } >&log2
diff -q $LOG log2 >&/dev/null || exit 1

{  $REDUCED_BIN .$ input2; } >&$LOG || exit 1
{  $ORIGIN_BIN .$ input2; } >&log2
diff -q $LOG log2 >&/dev/null || exit 1

{  $REDUCED_BIN \^ input2; } >&$LOG || exit 1
{  $ORIGIN_BIN \^ input2; } >&log2
diff -q $LOG log2 >&/dev/null || exit 1

{  $REDUCED_BIN \^$ input2; } >&$LOG || exit 1
{  $ORIGIN_BIN \^$ input2; } >&log2
diff -q $LOG log2 >&/dev/null || exit 1

{  $REDUCED_BIN ^[AEIOU] input2; } >&$LOG || exit 1
{  $ORIGIN_BIN ^[AEIOU] input2; } >&log2
diff -q $LOG log2 >&/dev/null || exit 1

{  $REDUCED_BIN ^[^AEIOU] input2; } >&$LOG || exit 1
{  $ORIGIN_BIN ^[^AEIOU] input2; } >&log2
diff -q $LOG log2 >&/dev/null || exit 1

{  $REDUCED_BIN -E "free[^[:space:]]+" input2; } >&$LOG || exit 1
{  $ORIGIN_BIN -E "free[^[:space:]]+" input2; } >&log2
diff -q $LOG log2 >&/dev/null || exit 1

{  $REDUCED_BIN -E '\b(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)' input; } >&$LOG || exit 1
{  $ORIGIN_BIN -E '\b(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)' input; } >&log2
diff -q $LOG log2 >&/dev/null || exit 1

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
