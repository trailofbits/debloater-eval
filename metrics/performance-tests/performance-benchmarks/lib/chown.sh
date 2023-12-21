#!/usr/bin/env bash

# ----- Common functionality
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
# shellcheck source=lib/core.sh
source "${SCRIPT_DIR}/core.sh"

# ----- Defaults
SYSTEM_CHOWN="$(which chown)"
WORKDIR="${SCRIPT_DIR}/../inputs/chown"
USER_GROUP="$(id -u):$(id -g)"
TEST_GROUP="foo:foo"

# ----- Input variables for benchmarking
: "${BIN:=$(which chown)}"

# ---- Helpers

function setup {
	useradd --user-group foo
}

function reset_owners {
	"${SYSTEM_CHOWN}" -R "${USER_GROUP}" "${WORKDIR}"
}

function cleanup {
	id foo >/dev/null 2>&1 && userdel --remove foo
	reset_owners
}

# ----- Benchmarking functions

function aggressive_own {
	debug "Owning (aggressive)"
	"${BIN}" "${TEST_GROUP}" "${WORKDIR}/file1"
	"${BIN}" "${TEST_GROUP}" "${WORKDIR}/d1/d1/d1/file"
}

function all {
	"${BIN}" "${TEST_GROUP}" "${WORKDIR}/file1"
	"${BIN}" "${TEST_GROUP}" "${WORKDIR}/d1/d1/d1/file"
	reset_owners
	"${BIN}" -R "${TEST_GROUP}" "${WORKDIR}/d1"
	"${BIN}" -h "${TEST_GROUP}" "${WORKDIR}/file1"
	reset_owners
	"${BIN}" -h "${TEST_GROUP}" "${WORKDIR}/symlink1"
	reset_owners
	"${BIN}" "${TEST_GROUP}" "${WORKDIR}/symlink1"
}
