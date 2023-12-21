FROM ubuntu:20.04

# Make sure Docker does not freeze while setting up the timezone
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential clang-format-10 lsb-release gdb git gosu libc6-dbg \
    libcapstone-dev libreadline-dev libboost-python-dev patchelf lcov gawk \
    time bison python3 python3-pip && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

CMD ["/bin/bash"]

ARG READ_TOKEN=changeme
WORKDIR /usr/src/
RUN git clone https://__token__:$READ_TOKEN@gitlab.tpcp.io/open-source/Egalito/libfilter.git
WORKDIR /usr/src/libfilter
RUN git checkout 2b4fd0a6eba4dd06eead1655da9795f5644fc704
RUN git submodule update --init --recursive
RUN make

# Libraries needed by our benchmarks
RUN apt-get update && apt-get install -y libgomp1 libomp-dev libjpeg-dev \
    libpng-dev libpcre2-dev libz-dev libssl-dev libboost-dev libopenjp2-7-dev \
    libfreetype-dev libfontconfig-dev gnutls-dev libmpfr-dev libevent-dev \
    libcrypt-dev
