FROM ubuntu:20.04

RUN dpkg --add-architecture i386
RUN apt-get update -y && DEBIAN_FRONTEND=noninteractive apt-get install -y build-essential clang cmake \
    g++-multilib gcc-multilib # -target i386-linux-elf <- for 32 bit

RUN apt-get -y install libc6-dev:i386

# Use gold linker by default to be more consistent against CFI binaries
RUN update-alternatives --install "/usr/bin/ld" "ld" "/usr/bin/ld.gold" 20 && \
    update-alternatives --install "/usr/bin/ld" "ld" "/usr/bin/ld.bfd" 10 && \
    update-alternatives --config ld

COPY benchmarks /usr/src/benchmarks
WORKDIR /usr/src/benchmarks
