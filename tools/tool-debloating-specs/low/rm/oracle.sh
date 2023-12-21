#!/bin/bash

REDUCED_BIN=./src/rm
ORIGIN_BIN=./rm.origin
LOG=log.txt

function run1() {
  touch file
  {  $REDUCED_BIN file; } >&$LOG
  r=$?
  a=1
  b=1
  if [[ $r -eq 0 && ! -f file ]]; then
    a=0
  fi
  /bin/rm -rf file
  {  $REDUCED_BIN file; } >&$LOG
  r=$?
  err=1
  if grep -q "No such file or directory" $LOG; then
    err=0
  fi
  if [[ $r -eq 1 && $err -eq 0 ]]; then
    b=0
  fi
  if [[ $a -eq 0 && $b -eq 0 ]]; then
    return 0
  else
    return 1
  fi
}


function run2() {
  mkdir dir
  {  $REDUCED_BIN -r dir; } >&$LOG
  r=$?
  a=1
  b=1
  if [[ $r -eq 0 && ! -d dir ]]; then
    a=0
  fi
  /bin/rm -rf dir
  mkdir dir
  {  $REDUCED_BIN -r -f dir; } >&$LOG
  r=$?
  if [[ $r -eq 0 && ! -d dir ]]; then
    b=0
  fi
  /bin/rm -rf dir
  if [[ $a -eq 0 && $b -eq 0 ]]; then
    return 0
  else
    return 1
  fi
}


function run3() {
  mkdir dir
  {  $REDUCED_BIN -f dir; } >&$LOG
  r=$?
  x=1
  if grep -q "cannot remove \`dir': Is a directory" $LOG; then
    x=0
  fi
  if [[ $r -eq 1 && $x -eq 0 ]]; then
    return 0
  else
    return 1
  fi
}


function run4() {
  touch filei
  {  echo "Y" |  $REDUCED_BIN -i filei; } >&$LOG
  r=$?
  if [[ $r -eq 0 && ! -f filei ]]; then
    return 0
  else
    clean
    return 1
  fi
  touch filei
  {  echo "N" |  $REDUCED_BIN -i filei; } >&$LOG
  r=$?
  if [[ $r -eq 0 && -f filei ]]; then
    return 0
  else
    clean
    return 1
  fi
  rm filei
}

# Desired Options: -r, -f, -i

run1 || exit 1
/bin/rm -rf file dir
run2 || exit 1
/bin/rm -rf file dir
run3 || exit 1
/bin/rm -rf file dir
run4 || exit 1
/bin/rm -rf file dir

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
