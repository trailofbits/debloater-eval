#!/usr/bin/env bash

set -euo pipefail

source "lib/pdftohtml.sh"

DEFAULT_BIN="${BIN}"

# ----- Input variables for benchmarking
BIN="${1:-${BIN}}"
: "${TIMES:=50}"

function usage {
	echo "usage: ${0} [<pdftohtml_binary_path>]"
	echo ""
	echo "Default pdftohtml path: '${DEFAULT_BIN}'"
	echo ""
	echo "Optional environment variables to set:"
	echo "          'TIMES': Number of times to run the scenario (${TIMES})"
	echo "   'SIMPLE_INPUT': Path to simple input file under test (${SIMPLE_INPUT})"
	echo "  'COMPLEX_INPUT': Path to complex input file under test (${COMPLEX_INPUT})"
	echo "        'VERBOSE': Print progress (${VERBOSE})"
}

if [[ "${1:-}" == "-h" ]]; then
	usage
	exit 0
fi

function scenario {
	simple
	opts_range
	single_doc
	complex
}

for round in $(seq "${TIMES}"); do
	debug "Round ${round}/${TIMES}"
	scenario
done
