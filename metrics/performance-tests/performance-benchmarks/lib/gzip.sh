#!/usr/bin/env bash

# ----- Common functionality
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
# shellcheck source=lib/core.sh
source "${SCRIPT_DIR}/core.sh"

# ----- Defaults
DEFAULT_COMPRESS_INPUT="${SCRIPT_DIR}/../inputs/gzip/sample1.ref"
DEFAULT_DECOMPRESS_INPUT="${SCRIPT_DIR}/../inputs/gzip/sample1.gz.ref"

# ----- Input variables for benchmarking
: "${BIN:=$(which gzip)}"
: "${COMPRESS_INPUT:=${DEFAULT_COMPRESS_INPUT}}"
: "${DECOMPRESS_INPUT:=${DEFAULT_DECOMPRESS_INPUT}}"

# ---- Helpers
function _assert_exists {
	file_exists "${1}" || die "Could not find file '${1}'"
}

# ----- Benchmarking functions

function aggressive_compress {
	_assert_exists "${COMPRESS_INPUT}"
	if [ "${CUT_ARGS}" = true ]; then
		debug "Aggressive Compressing (cut args)"
		"${BIN}" -v <"${COMPRESS_INPUT}" >"${COMPRESS_INPUT}.gz"
	else
		debug "Aggressive Compressing"
		"${BIN}" -c -f <"${COMPRESS_INPUT}" >"${COMPRESS_INPUT}.gz"
	fi
}

function compress {
	_assert_exists "${COMPRESS_INPUT}"
	debug "Compressing"
	"${BIN}" -c <"${COMPRESS_INPUT}" >"${COMPRESS_INPUT}.gz" 2>/dev/null
}

function decompress {
	_assert_exists "${DECOMPRESS_INPUT}"
	debug "Decompressing"
	"${BIN}" -d <"${DECOMPRESS_INPUT}" >"${DECOMPRESS_INPUT}.bin" 2>/dev/null
}
