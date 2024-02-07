FROM ubuntu:20.04

RUN apt-get update -y && apt-get install -y bear build-essential clang curl git \
      python3-pip python3-venv time
RUN pip3 install --upgrade 'pip>=20.3'
RUN python3 -m venv chisel_env
RUN . chisel_env/bin/activate && pip3 install --upgrade 'pip>=20.3'

ARG TPCP_ACCESS_TOKEN="<no access token specified>"

RUN . chisel_env/bin/activate && pip3 install chisel-asts==2.11.0 --index-url https://__token__:$TPCP_ACCESS_TOKEN@gitlab.tpcp.io/api/v4/projects/321/packages/pypi/simple

# Memcached's oracle depends on this package
RUN . chisel_env/bin/activate && python3 -m pip install pymemcache

# bftpd's oracle needs lftp
RUN apt-get install -y lftp

RUN . chisel_env/bin/activate && chisel --version

