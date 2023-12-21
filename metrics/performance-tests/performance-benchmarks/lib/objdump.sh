#!/usr/bin/env bash

# ----- Common functionality
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
# shellcheck source=lib/core.sh
source "${SCRIPT_DIR}/core.sh"

# ----- Defaults
DEFAULT_STATIC_INPUT="${SCRIPT_DIR}/../inputs/objdump/hyperfine"
DEFAULT_DYNAMIC_INPUT="${SCRIPT_DIR}/../inputs/objdump/ls"

# ----- Input variables for benchmarking
: "${BIN:=$(which objdump)}"
: "${STATIC_INPUT:=${DEFAULT_STATIC_INPUT}}"
: "${DYNAMIC_INPUT:=${DEFAULT_DYNAMIC_INPUT}}"

# ---- Helpers
function _assert_exists {
	file_exists "${1}" || die "Could not find file '${1}'"
}

objdump_opts=(-a -f -p -h -x -d -D -S -s -g -e -G -t -r -T -R)

function _dump {
	for opt in "${objdump_opts[@]}"; do
		"${BIN}" "${opt}" "${1}" >/dev/null 2>&1
	done
}

# ----- Benchmarking functions

function static {
	_assert_exists "${STATIC_INPUT}"
	debug "Static Binary"
	_dump "${STATIC_INPUT}"
}

function dynamic {
	_assert_exists "${DYNAMIC_INPUT}"
	debug "Dynamic Binary"
	_dump "${DYNAMIC_INPUT}"
}

function aggressive_static {
	_assert_exists "${STATIC_INPUT}"
	args=""
	if [ "${CUT_ARGS}" = true ]; then
		debug "Static Binary (aggressive) (cut args)"
	else
		debug "Static Binary (aggressive)"
		args="-x"
	fi
	"${BIN}" "${args}" "${STATIC_INPUT}" >/dev/null 2>&1
}

function aggressive_dynamic {
	_assert_exists "${DYNAMIC_INPUT}"
	args=""
	if [ "${CUT_ARGS}" = true ]; then
		debug "Dynamic Binary (aggressive) (cut args)"
	else
		debug "Dynamic Binary (aggressive)"
		args="-x"
	fi
	"${BIN}" "${args}" "${DYNAMIC_INPUT}" >/dev/null 2>&1
}
