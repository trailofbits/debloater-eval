# used to create ubuntu_stats:latest for batch-debloat-eval.batch2.json
FROM ubuntu:latest
RUN apt update
# install missing libraries
RUN apt install -y libcurl4 libjpeg62 libpcap0.8 libopenjp2-7
# install openssl-1.1.1v (libssl-1.1.so and libcrypto-1.1.so)
RUN apt install -y wget build-essential
RUN wget https://www.openssl.org/source/old/1.1.1/openssl-1.1.1v.tar.gz
RUN tar -xzf openssl-1.1.1v.tar.gz 
WORKDIR openssl-1.1.1v
RUN ./Configure linux-x86_64
RUN make
RUN make test
RUN make install
WORKDIR /
RUN ldconfig # update available libraries
