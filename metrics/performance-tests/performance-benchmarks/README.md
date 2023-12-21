# METIS Benchmarking Evaluation

This directory contains scripts that are used to benchmark debloated programs by running them through various scenarios in a script.

## Usage

Each script is named based on the binary tool that is being benchmarked, `benchmark_<tool>.sh`. Most scripts only require a single argument, the path to the binary. Some scripts could require multiple arguments for testing client/server tools.

Passing `-h` to any script will give a summary of how to run it and information about what can be changed.

## Intended Usage

This directory contains scripts for performance benchmarking, but the scripts do not have any benchmarking tools hard-coded. It is up to the script runner to monitor the performance of the tools being run in the script. The following shows an example using `/bin/time`.

```bash
sudo chrt -f 99 /bin/time -v ./benchmark_bzip2.sh "$(which bzip2)"
```

### Aggressive General Debloating Specs

Some debloating tools only support a single feature. To test these, there is another script `benchmark_aggressive_<tool>.sh` that will run a single test case against the binaries.

```bash
sudo chrt -f 99 /bin/time -v ./benchmark_aggressive_bzip2.sh "$(which bzip2)"
```

Moreover, some debloating tools will hard-code the static CLI arguments and only accept the dynamic portion, i.e. `rm -rf ./file` will be `rm_debloated ./file` and will internally use `-rf` semantics against the file path. To run these tests, you must set `CUT_ARGS` environment variable.

```bash
sudo CUT_ARGS=true chrt -f 99 /bin/time -v ./benchmark_aggressive_bzip2.sh "$(which debloated_bzip2)"
```

## Methodology

The benchmarked execution of each tool was created as a best-effort representation of common scenarios and use-cases. The exercised features may not cover the entire feature space or offer exact insights for precise performance comparison.

## Implementation

Each tool's benchmark consists of a top-level bash file named after the tool. This file contains a scenario (or multiple) function that runs common usage patterns for the tool. This scenario function runs individual tool functionality from the corresponding bash file in the [`lib`](./lib) directory.

Each bash file should be self-documenting with `debug` messages and programmed defensively by checking for the existence of needed files and notes on how to create or retrieve required files.
