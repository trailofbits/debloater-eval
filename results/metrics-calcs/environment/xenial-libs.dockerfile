# used to build libraries from Ubuntu xenial
FROM ubuntu:16.04
RUN apt update
RUN apt install -y \
libevent-2.0-5 \
libopenjpeg5 \
libpng12-0
