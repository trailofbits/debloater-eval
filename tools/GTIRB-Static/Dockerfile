FROM docker.tpcp.io/metis/omnibus/ci:0-2-2

RUN apt-get update -y && apt-get install time

# Libraries needed by our benchmarks
RUN apt-get update && apt-get install -y libgomp1 libomp-dev libjpeg-dev libpng-dev libpcre2-dev libz-dev libssl-dev libboost-dev libopenjp2-7-dev libfreetype-dev libfontconfig-dev gnutls-dev libmpfr-dev libevent-dev libcrypt-dev
