#!/usr/bin/env bash

# ----- Common functionality
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
# shellcheck source=lib/core.sh
source "${SCRIPT_DIR}/core.sh"

# ----- Defaults
DEFAULT_ROOT_DIR=/tmp/mkdir_benchmark

# ----- Input variables for benchmarking
: "${BIN:=$(which mkdir)}"
: "${ROOT_DIR:=${DEFAULT_ROOT_DIR}}"

# ---- Helpers

function cleanup {
	rm -r "${ROOT_DIR}"
}

# ----- Benchmarking functions

function aggressive_parents {
	args=""
	if [ "${CUT_ARGS}" = true ]; then
		debug "Parents (aggressive) (cut args)"
	else
		debug "Parents (aggressive)"
		args="-p"
	fi
	"${BIN}" ${args} "${ROOT_DIR}"
	(
		cd "${ROOT_DIR}" || exit 1
		# relative
		"${BIN}" ${args} d1
		# relative_parent
		"${BIN}" ${args} d1/d2
		# relative_parents
		"${BIN}" ${args} d1/d2/d3/d4
		# exists_ok
		"${BIN}" ${args} d1
		# exists_ok_parent
		"${BIN}" ${args} d1/d2
	)
}

function all {
	# absolute
	"${BIN}" "${ROOT_DIR}"
	(
		cd "${ROOT_DIR}" || exit 1
		# relative
		"${BIN}" d1
		# relative_parent
		"${BIN}" -p d1/d2
		# relative_parents
		"${BIN}" -p d1/d2/d3/d4
		# exists_ok
		"${BIN}" -p d1
		# exists_ok_parent
		"${BIN}" -p d1/d2
	)
}
