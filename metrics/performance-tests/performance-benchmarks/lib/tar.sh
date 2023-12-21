#!/usr/bin/env bash

# ----- Common functionality
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
# shellcheck source=lib/core.sh
source "${SCRIPT_DIR}/core.sh"

# ----- Defaults
DEFAULT_OUTPUT="${SCRIPT_DIR}/../inputs/tar/20mb.tar"
DEFAULT_INPUT1="${SCRIPT_DIR}/../inputs/tar/10mb_1.bin"
DEFAULT_INPUT2="${SCRIPT_DIR}/../inputs/tar/10mb_2.bin"
DEFAULT_EXPAND_INPUT="${SCRIPT_DIR}/../inputs/tar/expand.tar"

# ----- Input variables for benchmarking
: "${BIN:=$(which tar)}"
: "${OUTPUT:=${DEFAULT_OUTPUT}}"
: "${INPUT1:=${DEFAULT_INPUT1}}"
: "${INPUT2:=${DEFAULT_INPUT2}}"
: "${EXPAND_INPUT:=${DEFAULT_EXPAND_INPUT}}"

# ---- Helpers
function _assert_exists {
	file_exists "${1}" || die "Could not find file '${1}'"
}

# ----- Benchmarking functions

function aggressive_expand {
	_assert_exists "${EXPAND_INPUT}"
	if [ "${CUT_ARGS}" = true ]; then
		debug "Expand (aggressive) (cut args)"
		"${BIN}" "${EXPAND_INPUT}"
	else
		debug "Expand (aggressive)"
		"${BIN}" xf "${EXPAND_INPUT}"
	fi
}

function collect {
	debug "Collecting"
	"${BIN}" cf "${OUTPUT}" "${INPUT1}" "${INPUT2}"
}

function expand {
	_assert_exists "${OUTPUT}"
	debug "Expand"
	"${BIN}" xf "${OUTPUT}"
}

function zip {
	debug "Zipping"
	"${BIN}" cfz "${OUTPUT}.gz" "${INPUT1}" "${INPUT2}"
	rm "${OUTPUT}.gz"
}

function cleanup {
	rm -f "${OUTPUT}"
}
