#!/bin/bash

ORIGIN_BIN=./chown.origin
REDUCED_BIN=./src/chown
LOG=log.txt

# $1 : option, $2 : file for reduced, $3 : file for original
function run() {
  { $REDUCED_BIN $1 $(whoami):sudo $2; } >&$LOG || exit 1
  ls -al $2 | cut -d ' ' -f 4 >temp1
  $ORIGIN_BIN $1 $(whoami):sudo $3 >&/dev/null
  ls -al $3 | cut -d ' ' -f 4 >temp2
  diff -q temp1 temp2 >&/dev/null || exit 1

  { $REDUCED_BIN $1 $(whoami):$(whoami) $2; } >&$LOG || exit 1
  ls -al $2 | cut -d ' ' -f 4 >temp1
  $ORIGIN_BIN $1 $(whoami):$(whoami) $3 >&/dev/null
  ls -al $3 | cut -d ' ' -f 4 >temp2
  diff -q temp1 temp2 >&/dev/null || exit 1
  return 0
}


touch file1
touch file2
run "" file1 file2 || exit 1
rm -rf file1 file2

mkdir -p d1/d1/d1
touch d1/d1/d1/file
mkdir -p d2/d2/d2
touch d2/d2/d2/file
run "" d1/d1/d1/file d2/d2/d2/file || exit 1
rm -rf d1 d2

mkdir -p d1/d1/d1
touch d1/d1/d1/file
mkdir -p d2/d2/d2
touch d2/d2/d2/file
run "" d1 d2 || exit 1
ls -al d1/d1/d1/file | cut -d ' ' -f 4 >temp1
ls -al d2/d2/d2/file | cut -d ' ' -f 4 >temp2
diff -q temp1 temp2 >&/dev/null || exit 1
rm -rf d1 d2

mkdir -p d1/d1/d1
touch d1/d1/d1/file
mkdir -p d2/d2/d2
touch d2/d2/d2/file
run "-R" d1 d2 || exit 1
ls -al d1/d1/d1/file | cut -d ' ' -f 4 >temp1
ls -al d2/d2/d2/file | cut -d ' ' -f 4 >temp2
diff -q temp1 temp2 >&/dev/null || exit 1
rm -rf d1 d2

touch file1
touch file2
ln -s file1 symfile1
ln -s file2 symfile2
run "-h" file1 file2 || exit 1
rm -rf file1 file2 symfile1 symfile2

touch file1
touch file2
ln -s file1 symfile1
ln -s file2 symfile2
run "-h" symfile1 symfile2 || exit 1
rm -rf file1 file2 symfile1 symfile2

touch file1
touch file2
ln -s file1 symfile1
ln -s file2 symfile2
run "" symfile1 symfile2 || exit 1
rm -rf file1 file2 symfile1 symfile2

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
