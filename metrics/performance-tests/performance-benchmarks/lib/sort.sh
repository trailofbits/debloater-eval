#!/usr/bin/env bash

# ----- Common functionality
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
# shellcheck source=lib/core.sh
source "${SCRIPT_DIR}/core.sh"

# ----- Defaults
DEFAULT_INPUT="${SCRIPT_DIR}/../inputs/sort/shakespeare.txt"

# ----- Input variables for benchmarking
: "${BIN:=$(which sort)}"
: "${INPUT:=${DEFAULT_INPUT}}"

# ----- Benchmarking functions

function aggressive_unique_zero {
	if [ "${CUT_ARGS}" = true ]; then
		debug "Unique Zero (aggressive) (cut args)"
		"${BIN}" "${INPUT}" >/dev/null
	else
		debug "Unique Zero (aggressive)"
		"${BIN}" -u -z "${INPUT}" >/dev/null
	fi
}

function default {
	debug "Default"
	"${BIN}" "${INPUT}" >/dev/null
}

function reverse {
	debug "Reverse"
	"${BIN}" -r "${INPUT}" >/dev/null
}

function stabilize {
	debug "Stabilize"
	"${BIN}" -s "${INPUT}" >/dev/null
}

function unique {
	debug "Unique"
	"${BIN}" -u "${INPUT}" >/dev/null
}

function zero_terminate {
	debug "Zero Terminate"
	"${BIN}" -z "${INPUT}" >/dev/null
}
