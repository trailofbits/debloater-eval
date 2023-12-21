#!/bin/bash

ORIGIN_BIN=./date.origin
REDUCED_BIN=./src/date
LOG=log.txt


t0='08:17:48'
d0='1997-01-19'
d1="$d0 $t0 +0"
fmt="+%Y-%m-%d %T"
n_seconds=72057594037927935
touch f
$ORIGIN_BIN >&temp1
{  $REDUCED_BIN; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN --date '02/29/1996 1 year' +%Y-%m-%d >&temp1
{  $REDUCED_BIN --date '02/29/1996 1 year' +%Y-%m-%d; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN --date '1995-1-1' +%U >&temp1
{  $REDUCED_BIN --date '1995-1-1' +%U; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN --date '1995-1-7' +%U >&temp1
{  $REDUCED_BIN --date '1995-1-7' +%U; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN --date '1995-1-8' +%U >&temp1
{  $REDUCED_BIN --date '1995-1-8' +%U; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN --date '1992-1-1' +%U >&temp1
{  $REDUCED_BIN --date '1992-1-1' +%U; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN --date '1992-1-4' +%U >&temp1
{  $REDUCED_BIN --date '1992-1-4' +%U; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN --date '1992-1-5' +%U >&temp1
{  $REDUCED_BIN --date '1992-1-5' +%U; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN --date '1992-1-1' +%V >&temp1
{  $REDUCED_BIN --date '1992-1-1' +%V; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN --date '1992-1-5' +%V >&temp1
{  $REDUCED_BIN --date '1992-1-5' +%V; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN --date '1992-1-6' +%V >&temp1
{  $REDUCED_BIN --date '1992-1-6' +%V; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN --date '1992-1-1' +%W >&temp1
{  $REDUCED_BIN --date '1992-1-1' +%W; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN --date '1992-1-5' +%W >&temp1
{  $REDUCED_BIN --date '1992-1-5' +%W; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN --date '1992-1-6' +%W >&temp1
{  $REDUCED_BIN --date '1992-1-6' +%W; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN --date '1998-1-1 3 years' +%Y >&temp1
{  $REDUCED_BIN --date '1998-1-1 3 years' +%Y; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d 'TZ="America/Los_Angeles" 09:00 next Fri' >&temp1
{  $REDUCED_BIN -d 'TZ="America/Los_Angeles" 09:00 next Fri'; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d "$d1 now" "+%Y-%m-%d %T" >&temp1
{  $REDUCED_BIN -d "$d1 now" "+%Y-%m-%d %T"; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d "$d1 yesterday" "$fmt" >&temp1
{  $REDUCED_BIN -d "$d1 yesterday" "$fmt"; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d "$d1 tomorrow" "$fmt" >&temp1
{  $REDUCED_BIN -d "$d1 tomorrow" "$fmt"; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d "$d1 6 years ago" "$fmt" >&temp1
{  $REDUCED_BIN -d "$d1 6 years ago" "$fmt"; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d "$d1 7 months ago" "$fmt" >&temp1
{  $REDUCED_BIN -d "$d1 7 months ago" "$fmt"; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d "$d1 8 weeks ago" "$fmt" >&temp1
{  $REDUCED_BIN -d "$d1 8 weeks ago" "$fmt"; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN --rfc-3339=ns -d'1970-01-01 00:00:00.2234567 UTC +961062237.987654321 sec' >&temp1
{  $REDUCED_BIN --rfc-3339=ns -d'1970-01-01 00:00:00.2234567 UTC +961062237.987654321 sec'; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d '2005-03-27 +1 day' '+%Y' >&temp1
{  $REDUCED_BIN -d '2005-03-27 +1 day' '+%Y'; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d @-22 +%05s >&temp1
{  $REDUCED_BIN -d @-22 +%05s; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d @-22 +%_5s >&temp1
{  $REDUCED_BIN -d @-22 +%_5s; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

{ $ORIGIN_BIN -d "$n_seconds" 2>&1 | cut -d ' ' -f 3; } >&temp1
{  $REDUCED_BIN -d "$n_seconds"; } >&$LOG
diff -q <(cat temp1) <(cut -d ' ' -f 3 $LOG) >&/dev/null || exit 1

$ORIGIN_BIN -d 1999-12-08 +%_3d >&temp1
{  $REDUCED_BIN -d 1999-12-08 +%_3d; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d 1999-12-08 +%03d >&temp1
{  $REDUCED_BIN -d 1999-12-08 +%03d; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d "1999-12-08 7:30" "+%^c" >&temp1
{  $REDUCED_BIN -d "1999-12-08 7:30" "+%^c"; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN --rfc-3339=ns -d "2038-01-19 03:14:07.999999999" >&temp1
{  $REDUCED_BIN --rfc-3339=ns -d "2038-01-19 03:14:07.999999999"; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN --rfc-3339=sec -d @31536000 >&temp1
{  $REDUCED_BIN --rfc-3339=sec -d @31536000; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN --rfc-3339=date -d May-23-2003 >&temp1
{  $REDUCED_BIN --rfc-3339=date -d May-23-2003; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d '1999-06-01' '+%3004Y' >&temp1
{  $REDUCED_BIN -d '1999-06-01' '+%3004Y'; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN --utc -d '1970-01-01 UTC +961062237 sec' "$fmt" >&temp1
{  $REDUCED_BIN --utc -d '1970-01-01 UTC +961062237 sec' "$fmt"; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN --utc -d '1970-01-01 00:00:00 UTC +961062237 sec' "$fmt" >&temp1
{  $REDUCED_BIN --utc -d '1970-01-01 00:00:00 UTC +961062237 sec' "$fmt"; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -R -d "$d1" >&temp1
{  $REDUCED_BIN -R -d "$d1"; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d 000909 "$fmt" >&temp1
{  $REDUCED_BIN -d 000909 "$fmt"; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -u -d '1996-11-10 0:00:00 +0' "$fmt" >&temp1
{  $REDUCED_BIN -u -d '1996-11-10 0:00:00 +0' "$fmt"; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -u -d '1996-11-10 0:00:00 +0' "$fmt" >&temp1
{  $REDUCED_BIN -u -d '1996-11-10 0:00:00 +0' "$fmt"; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d "$d1 4 seconds ago" "$fmt" >&temp1
{  $REDUCED_BIN -d "$d1 4 seconds ago" "$fmt"; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d "$d1 4 seconds ago" "$fmt" >&temp1
{  $REDUCED_BIN -d "$d1 4 seconds ago" "$fmt"; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d '20050101  1 day' +%F >&temp1
{  $REDUCED_BIN -d '20050101  1 day' +%F; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d '20050101 +1 day' +%F >&temp1
{  $REDUCED_BIN -d '20050101 +1 day' +%F; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d "$d1 next second" '+%Y-%m-%d %T' >&temp1
{  $REDUCED_BIN -d "$d1 next second" '+%Y-%m-%d %T'; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d "$d1 next minute" '+%Y-%m-%d %T' >&temp1
{  $REDUCED_BIN -d "$d1 next minute" '+%Y-%m-%d %T'; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d "$d1 next hour" '+%Y-%m-%d %T' >&temp1
{  $REDUCED_BIN -d "$d1 next hour" '+%Y-%m-%d %T'; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d "$d1 next day" '+%Y-%m-%d %T' >&temp1
{  $REDUCED_BIN -d "$d1 next day" '+%Y-%m-%d %T'; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d "$d1 next week" '+%Y-%m-%d %T' >&temp1
{  $REDUCED_BIN -d "$d1 next week" '+%Y-%m-%d %T'; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d "$d1 next month" '+%Y-%m-%d %T' >&temp1
{  $REDUCED_BIN -d "$d1 next month" '+%Y-%m-%d %T'; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d "$d1 next year" '+%Y-%m-%d %T' >&temp1
{  $REDUCED_BIN -d "$d1 next year" '+%Y-%m-%d %T'; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -u -d '08/01/97 6:00' '+%D,%H:%M' >&temp1
{  $REDUCED_BIN -u -d '08/01/97 6:00' '+%D,%H:%M'; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -u -d '08/01/97 6:00 UTC +4 hours' '+%D,%H:%M' >&temp1
{  $REDUCED_BIN -u -d '08/01/97 6:00 UTC +4 hours' '+%D,%H:%M'; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -u --file=f '+%Y-%m-%d %T' >&temp1
{  $REDUCED_BIN -u --file=f '+%Y-%m-%d %T'; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -u --file=f '+%Y-%m-%d %T' >&temp1
{  $REDUCED_BIN -u --file=f '+%Y-%m-%d %T'; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d '1970-01-01 00:00:01' +%s >&temp1
{  $REDUCED_BIN -d '1970-01-01 00:00:01' +%s; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d '1970-01-01 00:00:01 UTC +2 hours' +%s >&temp1
{  $REDUCED_BIN -d '1970-01-01 00:00:01 UTC +2 hours' +%s; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d 2000-01-01 +%s >&temp1
{  $REDUCED_BIN -d 2000-01-01 +%s; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d '1970-01-01 UTC 946684800 sec' +'%Y-%m-%d %T %z' >&temp1
{  $REDUCED_BIN -d '1970-01-01 UTC 946684800 sec' +'%Y-%m-%d %T %z'; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d "$d0 $t0 this minute" "$fmt" >&temp1
{  $REDUCED_BIN -d "$d0 $t0 this minute" "$fmt"; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d "$d0 $t0 this hour" "$fmt" >&temp1
{  $REDUCED_BIN -d "$d0 $t0 this hour" "$fmt"; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d "$d0 $t0 this week" "$fmt" >&temp1
{  $REDUCED_BIN -d "$d0 $t0 this week" "$fmt"; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d "$d0 $t0 this month" "$fmt" >&temp1
{  $REDUCED_BIN -d "$d0 $t0 this month" "$fmt"; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d "$d0 $t0 this year" "$fmt" >&temp1
{  $REDUCED_BIN -d "$d0 $t0 this year" "$fmt"; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d "$d1 1 day ago" "$fmt" >&temp1
{  $REDUCED_BIN -d "$d1 1 day ago" "$fmt"; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d "$d1 2 hours ago" "$fmt" >&temp1
{  $REDUCED_BIN -d "$d1 2 hours ago" "$fmt"; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -d "$d1 3 minutes ago" "$fmt" >&temp1
{  $REDUCED_BIN -d "$d1 3 minutes ago" "$fmt"; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -f datefile >&temp1
{  $REDUCED_BIN -f datefile; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

$ORIGIN_BIN -r datefile >&temp1
{  $REDUCED_BIN -r datefile; } >&$LOG
diff -q temp1 $LOG >&/dev/null || exit 1

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
