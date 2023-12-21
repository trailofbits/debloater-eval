#!/usr/bin/env bash

# ----- Common functionality
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
# shellcheck source=lib/core.sh
source "${SCRIPT_DIR}/core.sh"

# ----- Defaults
DEFAULT_INPUT="${SCRIPT_DIR}/../inputs/uniq/input.txt"

# ----- Input variables for benchmarking
: "${BIN:=$(which uniq)}"
: "${INPUT:=${DEFAULT_INPUT}}"

# ---- Helpers
function _assert_exists {
	file_exists "${1}" || die "Could not find file '${1}'"
}

# ----- Benchmarking functions

function aggressive_ignore_case {
	_assert_exists "${INPUT}"
	if [ "${CUT_ARGS}" = true ]; then
		debug "Ignore Case (aggressive) (cut args)"
		"${BIN}" "${INPUT}" >/dev/null
	else
		debug "Ignore Case (aggressive)"
		"${BIN}" -i "${INPUT}" >/dev/null
	fi
}

function stdin {
	_assert_exists "${INPUT}"
	"${BIN}" <<<"${INPUT}" >/dev/null
}

function stdin_count {
	_assert_exists "${INPUT}"
	"${BIN}" -c <<<"${INPUT}" >/dev/null
}

function stdin_repeated {
	_assert_exists "${INPUT}"
	"${BIN}" -d <<<"${INPUT}" >/dev/null
}

function stdin_only_uniq {
	_assert_exists "${INPUT}"
	"${BIN}" -u <<<"${INPUT}" >/dev/null
}

function stdin_ignore_case {
	_assert_exists "${INPUT}"
	"${BIN}" -i <<<"${INPUT}" >/dev/null
}

function stdin_skip_fields {
	_assert_exists "${INPUT}"
	"${BIN}" -f 5 <<<"${INPUT}" >/dev/null
}

function stdin_skip_chars {
	_assert_exists "${INPUT}"
	"${BIN}" -s 10 <<<"${INPUT}" >/dev/null
}

function stdin_first_chars {
	_assert_exists "${INPUT}"
	"${BIN}" -w 10 <<<"${INPUT}" >/dev/null
}
