FROM ubuntu:20.04

# Install python and dependencies needed to build gzip
RUN apt-get update -y && \
    DEBIAN_FRONTEND=noninteractive \
    apt-get install -y build-essential cmake curl git python3-pip unzip wget \
    time emacs-nox python pip  # python 2 for the harness that runs the razor specs

RUN pip3 install --upgrade pip

# Install ddisasm and gtirb-pprinter
RUN wget -O - https://download.grammatech.com/gtirb/files/apt-repo/conf/apt.gpg.key | apt-key add -
RUN echo "deb https://download.grammatech.com/gtirb/files/apt-repo focal stable"| tee -a /etc/apt/sources.list
RUN apt-get update -y && apt-get install -y ddisasm-1.5.6 gtirb-pprinter-1.8.6

ARG READ_TOKEN=changeme

# Clone a specific commit of gtirb-block-trace
RUN git clone https://__token__:$READ_TOKEN@gitlab.tpcp.io/bullpen/gtirb/gtirb-transforms/gtirb-block-trace.git \
    /usr/src/gtirb-block-trace
WORKDIR /usr/src/gtirb-block-trace
RUN git checkout 46579ecd6cbd00531f9dfce862796d21eef545d8

# Clone a specific commit of gtirb-reduce
RUN git clone https://__token__:$READ_TOKEN@gitlab.tpcp.io/metis/omnibus-dependencies/gtirb-reduce.git \
    /usr/src/gtirb-reduce
WORKDIR /usr/src/gtirb-reduce
RUN git checkout f209c8014061e46a5de9f8bbd8397979dfe0c297

# Clone a specific commit of gtirb-reachable
RUN git clone https://__token__:$READ_TOKEN@gitlab.tpcp.io/metis/omnibus-dependencies/gtirb-reachable.git \
    /usr/src/gtirb-reachable
WORKDIR /usr/src/gtirb-reachable
RUN git checkout 82d770eff982fd2b1b3f0b021528af5031e05b47

# Build and install gtirb-block-trace
RUN mkdir /usr/src/gtirb-block-trace/build
WORKDIR /usr/src/gtirb-block-trace/build
RUN cmake ..
RUN make
COPY ./requirements.txt ./requirements.txt
RUN pip3 install -r requirements.txt
