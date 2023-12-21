This directory contains files to run performance tests on original (non-debloated) benchmarks and collect metrics.
Metrics are saved to `binary_metrics.csv`.

To run general performance tests on benchmarks built on Ubuntu 20:

	python run_perf_tests.py

To  run aggressive performance tests on benchmarks built on Ubuntu 20:

	python run_perf_tests.py --type aggressive

To run general performance tests on benchmarks built on Debian-Buster:

	python run_perf_tests.py --os debian-buster

