# From: https://github.com/aspire-project/chisel/blob/master/docker/Dockerfile

FROM debian:buster

RUN apt-get update && apt-get install -y software-properties-common wget gnupg time g++
RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add -
RUN apt-add-repository "deb http://apt.llvm.org/buster/ llvm-toolchain-buster-8 main" && apt-get update
RUN apt-get install -y clang-8 libclang-8-dev llvm-8-dev cmake git wget
RUN apt-get install -y libspdlog-dev nlohmann-json-dev
RUN apt-get install -y libmlpack-dev
RUN ln -s /usr/bin/clang-8 /usr/bin/clang && ln -s /usr/bin/llvm-config-8 /usr/bin/llvm-config

RUN git clone https://github.com/aspire-project/chisel
RUN cd chisel && git checkout dfa757f
RUN git clone https://github.com/aspire-project/chiselbench
RUN cd chiselbench && git checkout 490ae19

RUN mkdir -p chisel/build && cd chisel/build && CXX=clang cmake .. && make

# Install clang 10, which is what we get on ubuntu 20
RUN apt-get remove -y clang-8
RUN apt-add-repository "deb http://apt.llvm.org/buster/ llvm-toolchain-buster-10 main" && apt-get update
RUN apt-get install -y clang-10 clang++-10
RUN rm /usr/bin/clang
RUN ln -s /usr/bin/clang-10 /usr/bin/clang
RUN ln -s /usr/bin/clang++-10 /usr/bin/clang++


ENV PATH /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/chisel/build/bin
ENV CC clang
ENV CHISEL_BENCHMARK_HOME /chiselbench
