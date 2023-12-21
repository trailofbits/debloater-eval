#!/bin/bash

set -e

if [ $# -lt 1 ] ; then
  echo "Usage: $0 gzip.exe"
  exit
fi
for test_file in logo.png  README  uuids1  uuids2  uuids3; do
  "$1" -c data/$test_file > /dev/null || exit $?
done
