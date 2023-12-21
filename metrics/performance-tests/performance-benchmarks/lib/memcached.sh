#!/usr/bin/env bash

# ----- Common functionality
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
# shellcheck source=lib/core.sh
source "${SCRIPT_DIR}/core.sh"

# ----- Defaults

# ----- Input variables for benchmarking
: "${BIN:=$(which memcached)}"

# ---- Helpers

# Server process ID
SERVER_PID=0

function start_server {
	"${BIN}" &
	SERVER_PID=$!
}

function cleanup {
	wait_kill ${SERVER_PID}
	SERVER_PID=0
}

function client_exec {
	python3 <<EOF
from memcache import Client
client = Client(['127.0.0.1'])
${1}
EOF
}

function c_flush {
	echo "client.flush_all()"
}

# ----- Benchmarking functions

# The 'c_*' functions return commands for the client

function c_set_get {
	echo "assert client.set('a', '10')
assert client.get('a') == '10'"
}

function c_add {
	echo "assert client.add('b', '10')
assert client.get('b') == '10', 'value was not set'"
}

function c_add_existing {
	echo "client.set('c', '10')
assert client.add('c', '20') == 0
assert client.get('c') == '10', 'value was updated'"
}

function c_replace {
	echo "assert client.add('d', '10')
assert client.replace('d', '20')
assert client.get('d') == '20', 'value was not replaced'"
}

function c_replace_exists {
	echo "assert client.replace('e', '10') == 0
assert client.get('e') is None, 'value was added'"
}

function c_append {
	echo "assert client.add('f', '10')
assert client.append('f', '00')
assert client.get('f') == '1000', 'value was not updated'"
}

function c_append_error {
	echo "assert client.append('g', '00') == 0
assert client.get('g') is None, 'value was set'"
}

function c_prepend {
	echo "assert client.add('h', '10')
assert client.prepend('h', '00')
assert client.get('h') == '0010', 'value was not updated'"
}

function c_prepend_error {
	echo "assert client.prepend('i', '00') == 0
assert client.get('i') is None, 'value was set'"
}

function c_delete {
	echo "assert client.add('j', '10')
assert client.delete('j')
assert client.get('j') is None, 'value was not deleted'"
}

function c_delete_error {
	echo "assert client.delete('k')"
}

function c_incr {
	echo "assert client.set('l', '10')
assert client.incr('l')
assert client.get('l') == '11'"
}

function c_incr_error {
	echo "assert client.incr('m') is None
assert client.get('m') is None"
}

function c_decr {
	echo "assert client.set('n', '10')
assert client.decr('n')
assert client.get('n') == '9 '"
}

function c_decr_error {
	echo "assert client.decr('o') is None
assert client.get('o') is None"
}
