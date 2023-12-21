#!/usr/bin/env bash

# ----- Common functionality
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
# shellcheck source=lib/core.sh
source "${SCRIPT_DIR}/core.sh"

# ----- Defaults
DEFAULT_ROOT_DIR=/tmp/rm_benchmark

# ----- Input variables for benchmarking
: "${BIN:=$(which rm)}"
: "${ROOT_DIR:=${DEFAULT_ROOT_DIR}}"

# ---- Helpers

function create {
	mkdir -p "${ROOT_DIR}/dir1/dir2/dir3/dir4"
	touch "${ROOT_DIR}/file0.txt" \
		"${ROOT_DIR}/file1.txt" \
		"${ROOT_DIR}/dir1/file1.txt" \
		"${ROOT_DIR}/dir1/dir2/dir3/dir4/file4.txt"
}

# ----- Benchmarking functions

function aggressive_force {
	args=""
	if [ "${CUT_ARGS}" = true ]; then
		debug "Force removing (aggressive) (cut args)"
	else
		debug "Force removing (aggressive)"
		args="-rf"
	fi
	"${BIN}" ${args} "${ROOT_DIR}/dir1/dir2"
	"${BIN}" ${args} "${ROOT_DIR}/dir1/file1.txt"
	"${BIN}" ${args} "${ROOT_DIR}"
	"${BIN}" ${args} "${ROOT_DIR}/dir1/dir2"
}

function all {
	"${BIN}" "${ROOT_DIR}/dir1/file1.txt"
	"${BIN}" -r -f "${ROOT_DIR}/dir1"
	# shellcheck disable=SC2216
	printf "Y\n" | "${BIN}" -i "${ROOT_DIR}/file0.txt"
	# shellcheck disable=SC2216
	printf "N\n" | "${BIN}" -i "${ROOT_DIR}/file1.txt"
	"${BIN}" "${ROOT_DIR}/file0.txt" || true
	"${BIN}" -f "${ROOT_DIR}" || true
	"${BIN}" || true
	"${BIN}" -r "${ROOT_DIR}"
}
