#!/usr/bin/env bash

set -euo pipefail

source "lib/chown.sh"

DEFAULT_BIN="${BIN}"

# ----- Input variables for benchmarking
BIN=${1:-${BIN}}
: "${TIMES:=100}"

function usage {
	echo "usage: ${0} [<chown_binary_path>]"
	echo ""
	echo "This test creates and deletes a user and group (${TEST_GROUP})."
	echo "You must have necessary permissions to run this (root)"
	echo ""
	echo "Default chown path: '${DEFAULT_BIN}'"
	echo ""
	echo "Optional environment variables to set:"
	echo "     'TIMES': Number of times to run the scenario (${TIMES})"
	echo "   'VERBOSE': Print progress (${VERBOSE})"
}

if [[ "${1:-}" == "-h" ]]; then
	usage
	exit 0
fi

function scenario {
	aggressive_own
}

trap "cleanup" SIGINT SIGTERM EXIT

setup

for round in $(seq "${TIMES}"); do
	reset_owners
	debug "Round ${round}/${TIMES}"
	scenario
done

cleanup
