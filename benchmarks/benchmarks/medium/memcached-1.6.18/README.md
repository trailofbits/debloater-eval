# Build Instructions

## Trimmer

```
apt install autotools-dev automake libevent-dev
cd ./source/memcached
./autogen.sh
FORCE_UNSAFE_CONFIGURE=1 CC=wllvm CFLAGS="-O0 -Xclang -disable-O0-optnone -fPIC -fPIE" LDFLAGS="-pie" ./configure
make
```
