#!/usr/bin/env bash

set -euo pipefail

source "lib/date.sh"

DEFAULT_BIN="${BIN}"

# ----- Input variables for benchmarking
BIN="${1:-${BIN}}"
: "${TIMES:=20}"

function usage {
	echo "usage: ${0} [<date_binary_path>]"
	echo ""
	echo "Default date path: '${DEFAULT_BIN}'"
	echo ""
	echo "Optional environment variables to set:"
	echo "     'TIMES': Number of times to run the scenario (${TIMES})"
	echo "       'DAY': Day of the month to use (${DAY})"
	echo "   'VERBOSE': Print progress (${VERBOSE})"
	echo "  'CUT_ARGS': Remove static CLI arguments (${CUT_ARGS})"
}

if [[ "${1:-}" == "-h" ]]; then
	usage
	exit 0
fi

function scenario {
	aggressive_date
}

for round in $(seq "${TIMES}"); do
	debug "Round ${round}/${TIMES}"
	scenario
done
