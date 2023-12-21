#!/usr/bin/env bash

set -euo pipefail

source "lib/uniq.sh"

DEFAULT_BIN="${BIN}"

# ----- Input variables for benchmarking
BIN=${1:-${BIN}}
: "${TIMES:=300}"

function usage {
	echo "usage: ${0} [<uniq_binary_path>]"
	echo ""
	echo "Default uniq path: '${DEFAULT_BIN}'"
	echo ""
	echo "Optional environment variables to set:"
	echo "    'TIMES': Number of times to run the scenario (${TIMES})"
	echo "    'INPUT': Path to input file under test (${INPUT})"
	echo "  'VERBOSE': Print progress (${VERBOSE})"
}

if [[ "${1:-}" == "-h" ]]; then
	usage
	exit 0
fi

function scenario {
	stdin
	stdin_count
	stdin_repeated
	stdin_only_uniq
	stdin_ignore_case
	stdin_skip_fields
	stdin_skip_chars
	stdin_first_chars
}

for round in $(seq "${TIMES}"); do
	debug "Round ${round}/${TIMES}"
	scenario
done
