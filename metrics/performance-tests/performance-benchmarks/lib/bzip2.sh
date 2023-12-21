#!/usr/bin/env bash

# ----- Common functionality
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
# shellcheck source=lib/core.sh
source "${SCRIPT_DIR}/core.sh"

# ----- Defaults
DEFAULT_INPUT="${SCRIPT_DIR}/../inputs/bzip2/20mb.bin"

# ----- Input variables for benchmarking
: "${BIN:=$(which bzip2)}"
: "${INPUT:=${DEFAULT_INPUT}}"

# ---- Initialize data
file_exists "${DEFAULT_INPUT}" || head -c 20MB /dev/urandom >"${DEFAULT_INPUT}"

# ---- Helpers
function _assert_exists {
	file_exists "${1}" || die "Could not find file '${1}'"
}

# ----- Benchmarking functions

function compress {
	_assert_exists "${INPUT}"
	debug "Compressing"
	"${BIN}" -c <"${INPUT}" >"${INPUT}.bz2"
}

function aggressive_compress {
	_assert_exists "${INPUT}"
	if [ "${CUT_ARGS}" = true ]; then
		debug "Compressing (aggressive) (cut args)"
		"${BIN}" -v <"${INPUT}" >"${INPUT}.bz2"
	else
		debug "Compressing (aggressive)"
		"${BIN}" -c -f <"${INPUT}" >"${INPUT}.bz2"
	fi
}

function decompress {
	_assert_exists "${INPUT}.bz2"
	debug "Decompressing"
	"${BIN}" -d <"${INPUT}.bz2" >"${INPUT}.tst"
}

function test_integrity_compressed {
	_assert_exists "${INPUT}.bz2"
	debug "Testing Integrity"
	"${BIN}" -t "${INPUT}.bz2"
}

function cleanup {
	rm -f "${INPUT}.tst"
	rm -f "${INPUT}.bz2"
}
