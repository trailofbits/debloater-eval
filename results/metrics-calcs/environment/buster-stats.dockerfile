# used to create buster_stats:latest for batch-debloat-eval.batch2.json
FROM debian:buster
RUN apt update
# install libraries
RUN apt install -y libevent-2.1-6 libnettle6 libssl1.1
