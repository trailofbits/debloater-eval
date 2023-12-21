#!/bin/sh
# dependencies for ubuntu binaries
sudo apt update
# install missing libraries
sudo apt install -y libcurl4 libjpeg62 libpcap0.8 libopenjp2-7
# install openssl-1.1.1v (libssl-1.1.so and libcrypto-1.1.so)
sudo apt install -y wget build-essential
wget https://www.openssl.org/source/old/1.1.1/openssl-1.1.1v.tar.gz
tar -xzf openssl-1.1.1v.tar.gz 
cd openssl-1.1.1v
./Configure linux-x86_64
make
make test
make install
cd ..
ldconfig # update available libraries