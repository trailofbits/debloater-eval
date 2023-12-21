#!/bin/bash
set -x
set -e

# This script debloats one of our benchmarks, run it from the root directory of the repository.
# Build the chisel-2 image from the Dockerfile in the chisel-2 directory

benchmark_full=$1 # Should look like low/uniq-8.16
benchmark=$(basename $benchmark_full) # Looks like uniq-8.16
benchmark_simple=${benchmark_full//-?*/} # Looks like low/uniq
benchmark_binary=$(basename $benchmark_simple) # looks like uniq
container_name="chisel-2-$benchmark"

num_processes=8

# Start container
sudo rm -rf $(pwd)/chisel-2-results/$benchmark_simple
docker run \
       --name $container_name \
       --memory 8g \
       --cpus=$num_processes \
       -d \
       --network=host \
       -v $(pwd):/host:rw \
       -v $(pwd)/chisel-2-results/$benchmark_simple:/chisel:rw \
       chisel-2 \
       tail -f /dev/null


function dexec {
  docker exec $container_name "$@"
}

# Install needed packages in container
dexec apt-get update -y
docker exec -e DEBIAN_FRONTEND=NONINTERACTIVE $container_name apt-get install -y $(python3 chisel-2/list-packages.py $benchmark_full)

# Setup run directory
#  - move source into position
#  - move origin binary into position
dexec mkdir /chisel/$benchmark
source_subdir=$(python3 -m yq -rM ".\"$benchmark_full\".\"source-dir\"" build-binaries/binaries.yml)
dexec /bin/bash -c "cp -r /host/benchmarks/$benchmark_full/source/$source_subdir/* /chisel/$benchmark"

# The low benchmark oracles use the *.origin binaries for testing against, and they also need the input files to be
# in the same directory as the source.
if [[ $benchmark_full =~ low/.* ]]; then
  dexec cp /host/benchmarks/$benchmark_full/binaries/64/$benchmark_binary /chisel/$benchmark/$benchmark_binary.origin
fi

# Prepare the source files and spec.
PYTHONPATH="$PYTHONPATH:$(pwd)/build-binaries" python3 chisel-2/prepare-source.py $benchmark_full $container_name

# run /usr/bin/time chisel with docker exec under a gnu screen. save the log from screen somewhere
mkdir -p chisel-2-logs
rm -f chisel-2-logs/$benchmark
screen -dmS chisel-2-$benchmark -L -Logfile chisel-2-logs/$benchmark \
       docker exec -w /chisel/$benchmark  $container_name \
       /bin/bash -c ". /chisel_env/bin/activate && \
       /usr/bin/time -q -f %e,%S,%U,%M,%t,%K,%x -o /chisel/metrics.csv \
       timeout --signal SIGINT 2d chisel reduce\
       --jobs=8 --spec /chisel/$benchmark/chisel-2-spec.yml \
       /chisel/$benchmark \
       /chisel/results"
