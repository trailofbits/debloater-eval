# used to build libraries from Ubuntu bionic
FROM ubuntu:18.04
RUN apt update
RUN apt install -y \
libilmbase12 \
openexr \
libssl1.0.0 \
libevent-2.1-6 \
libffi6 \
libnettle6 \
libwebp6
