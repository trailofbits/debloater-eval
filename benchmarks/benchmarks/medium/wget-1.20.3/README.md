# Build Instructions

## Trimmer

```
cd source/wget
apt install -y flex autoconf automake autoconf-archive
./bootstrap
gettextize -f
aclocal -I m4
autoconf
FORCE_UNSAFE_CONFIGURE=1 CC=wllvm CFLAGS="-O0 -Xclang -disable-O0-optnone -fPIC -fPIE" LDFLAGS="-pie" ./configure
make
```
