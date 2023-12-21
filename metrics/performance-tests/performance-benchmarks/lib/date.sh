#!/usr/bin/env bash

# ----- Common functionality
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
# shellcheck source=lib/core.sh
source "${SCRIPT_DIR}/core.sh"

# ----- Defaults
DEFAULT_DAY="1"

# ----- Input variables for benchmarking
: "${BIN:=$(which date)}"
: "${DAY:=${DEFAULT_DAY}}"

# ----- Benchmarking functions

function aggressive_date {
	args=""
	if [ "${CUT_ARGS}" = true ]; then
		debug "Converting (aggressive) (cut args)"
	else
		debug "Converting (aggressive)"
		args="-d"
	fi
	"${BIN}" ${args} "1997-01-19 08:17:48 +0 now" "+%Y-%m-%d %T"
	"${BIN}" ${args} "1997-01-19 08:17:48 +0 yesterday" "+%Y-%m-%d %T"
	"${BIN}" ${args} "1997-01-19 08:17:48 +0 tomorrow" "+%Y-%m-%d %T"
	"${BIN}" ${args} "1997-01-19 08:17:48 +0 6 years ago" "+%Y-%m-%d %T"
	"${BIN}" ${args} "1997-01-19 08:17:48 +0 7 months ago" "+%Y-%m-%d %T"
	"${BIN}" ${args} "1997-01-19 08:17:48 +0 8 weeks ago" "+%Y-%m-%d %T"
	"${BIN}" ${args} "1997-01-19 08:17:48 +0 next second" '+%Y-%m-%d %T'
	"${BIN}" ${args} "1997-01-19 08:17:48 +0 next minute" '+%Y-%m-%d %T'
	"${BIN}" ${args} "1997-01-19 08:17:48 +0 next hour" '+%Y-%m-%d %T'
	"${BIN}" ${args} "1997-01-19 08:17:48 +0 next day" '+%Y-%m-%d %T'
	"${BIN}" ${args} "1997-01-19 08:17:48 +0 next week" '+%Y-%m-%d %T'
	"${BIN}" ${args} "1997-01-19 08:17:48 +0 next month" '+%Y-%m-%d %T'
	"${BIN}" ${args} "1997-01-19 08:17:48 +0 next year" '+%Y-%m-%d %T'
}

function test_all {
	"${BIN}" --date "1996-1-${DAY}" +%U
	"${BIN}" --date "1996-1-${DAY}" +%W
	"${BIN}" --date "1996-1-${DAY}" +%V
	"${BIN}" --date '1998-1-1 3 years' +%Y
	"${BIN}" -d 'TZ="America/Los_Angeles" 09:00 next Fri'
	"${BIN}" -d "1997-01-19 08:17:48 +0 now" "+%Y-%m-%d %T"
	"${BIN}" -d "1997-01-19 08:17:48 +0 yesterday" "+%Y-%m-%d %T"
	"${BIN}" -d "1997-01-19 08:17:48 +0 tomorrow" "+%Y-%m-%d %T"
	"${BIN}" -d "1997-01-19 08:17:48 +0 6 years ago" "+%Y-%m-%d %T"
	"${BIN}" -d "1997-01-19 08:17:48 +0 7 months ago" "+%Y-%m-%d %T"
	"${BIN}" -d "1997-01-19 08:17:48 +0 8 weeks ago" "+%Y-%m-%d %T"
	"${BIN}" --rfc-3339=ns -d'1970-01-01 00:00:00.2234567 UTC +961062237.987654321 sec'
	"${BIN}" -d '2005-03-27 +1 day' '+%Y'
	"${BIN}" -d @-22 +%05s
	"${BIN}" -d @-22 +%_5s
	# "${BIN}" -d "72057594037927935"
	"${BIN}" -d 1999-12-08 +%_3d
	"${BIN}" -d 1999-12-08 +%03d
	"${BIN}" -d "1999-12-08 7:30" "+%^c"
	"${BIN}" --rfc-3339=ns -d "2038-01-19 03:14:07.999999999"
	"${BIN}" --rfc-3339=sec -d @31536000
	"${BIN}" --rfc-3339=date -d May-23-2003
	"${BIN}" -d '1999-06-01' '+%3004Y'
	"${BIN}" --utc -d '1970-01-01 UTC +961062237 sec' "+%Y-%m-%d %T"
	"${BIN}" --utc -d '1970-01-01 00:00:00 UTC +961062237 sec' "+%Y-%m-%d %T"
	"${BIN}" -R -d "1997-01-19 08:17:48 +0"
	"${BIN}" -d 000909 "+%Y-%m-%d %T"
	"${BIN}" -u -d '1996-11-10 0:00:00 +0' "+%Y-%m-%d %T"
	"${BIN}" -d "1997-01-19 08:17:48 +0 4 seconds ago" "+%Y-%m-%d %T"
	"${BIN}" -d '20050101  1 day' +%F
	"${BIN}" -d '20050101 +1 day' +%F
	"${BIN}" -d "1997-01-19 08:17:48 +0 next second" '+%Y-%m-%d %T'
	"${BIN}" -d "1997-01-19 08:17:48 +0 next minute" '+%Y-%m-%d %T'
	"${BIN}" -d "1997-01-19 08:17:48 +0 next hour" '+%Y-%m-%d %T'
	"${BIN}" -d "1997-01-19 08:17:48 +0 next day" '+%Y-%m-%d %T'
	"${BIN}" -d "1997-01-19 08:17:48 +0 next week" '+%Y-%m-%d %T'
	"${BIN}" -d "1997-01-19 08:17:48 +0 next month" '+%Y-%m-%d %T'
	"${BIN}" -d "1997-01-19 08:17:48 +0 next year" '+%Y-%m-%d %T'
	"${BIN}" -u -d '08/01/97 6:00' '+%D,%H:%M'
	"${BIN}" -u -d '08/01/97 6:00 UTC +4 hours' '+%D,%H:%M'
	# "${BIN}" -u --file=f '+%Y-%m-%d %T'
	"${BIN}" -d '1970-01-01 00:00:01' +%s
	"${BIN}" -d '1970-01-01 00:00:01 UTC +2 hours' +%s
	"${BIN}" -d 2000-01-01 +%s
	"${BIN}" -d '1970-01-01 UTC 946684800 sec' +'%Y-%m-%d %T %z'
	"${BIN}" -d "1997-01-19 08:17:48 this minute" "+%Y-%m-%d %T"
	"${BIN}" -d "1997-01-19 08:17:48 this hour" "+%Y-%m-%d %T"
	"${BIN}" -d "1997-01-19 08:17:48 this week" "+%Y-%m-%d %T"
	"${BIN}" -d "1997-01-19 08:17:48 this month" "+%Y-%m-%d %T"
	"${BIN}" -d "1997-01-19 08:17:48 this year" "+%Y-%m-%d %T"
	"${BIN}" -d "1997-01-19 08:17:48 +0 1 day ago" "+%Y-%m-%d %T"
	"${BIN}" -d "1997-01-19 08:17:48 +0 2 hours ago" "+%Y-%m-%d %T"
	"${BIN}" -d "1997-01-19 08:17:48 +0 3 minutes ago" "+%Y-%m-%d %T"

}
