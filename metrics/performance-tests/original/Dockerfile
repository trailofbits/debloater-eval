FROM ubuntu:20.04

RUN apt-get update -y && \
    DEBIAN_FRONTEND=noninteractive \
    apt-get install -y time libevent-dev libssl-dev \
    libnss3 libopenjp2-7-dev libtiff-dev libpng-dev libfontconfig-dev libjpeg-dev \
    libgomp1 libomp-dev \
    python3-pip \
    wget \
    lftp


RUN pip3 install --upgrade pip

RUN pip3 install python-memcached
