#!/bin/bash

LOG=log.txt
REDUCED_BIN=./bzip2
ORIGIN_BIN=./bzip2.origin

# -c
{ $REDUCED_BIN -c <references/sample1.ref >sample1.rb2; } &>$LOG || exit 1
cmp references/sample1.bz2.ref sample1.rb2 >&/dev/null || exit 1
# -d
{ $REDUCED_BIN -d <references/sample1.bz2.ref >sample1.tst; } &>$LOG || exit 1
cmp references/sample1.ref sample1.tst >&/dev/null || exit 1
# -f
echo "1234" >foo
{ $REDUCED_BIN -f foo; } >&$LOG || exit 1
# -t
echo "1234" >foo
{ $REDUCED_BIN -t foo; } >&$LOG && exit 1
{ $REDUCED_BIN -t references/sample1.bz2.ref; } >&$LOG || exit 1
# -k
rm foo*
echo "1234" >foo
{ $REDUCED_BIN -k foo; } >&$LOG || exit 1
test -f foo -a -f foo.bz2 || exit 1

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
