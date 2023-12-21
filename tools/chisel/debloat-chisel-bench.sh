#!/bin/bash

set -x
set -e

# Debloats one of the low, merged benchmarks in chisel bench
benchmark_full=$1 # This parameter should look like "uniq-8.16"
container_name=chisel-$benchmark_full

# Start docker container
docker run \
       --name $container_name \
       --cpus=1 \
       --memory=8g \
       -d \
       --network=host \
       chisel \
       tail -f /dev/null

# Start a screen and run `make reduce` under /usr/bin/time
mkdir -p chisel-logs
rm -f chisel-logs/$benchmark_full
screen -dmS chisel-$benchmark_full -L -Logfile chisel-logs/$benchmark_full \
       docker exec -it -w /chiselbench $container_name \
       /bin/bash -c "source setenv && cd benchmark/$benchmark_full/merged && /usr/bin/time -q -f %e,%S,%U,%M,%t,%K,%x -o /metrics.csv make reduce"
