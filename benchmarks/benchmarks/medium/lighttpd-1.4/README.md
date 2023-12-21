# Build Instructions

## Trimmer

```
apt install -y autoconf automake libtool m4 libpcre3-dev libpcre2-dev pkg-config
cd source/lighttpd1.4
./autogen.sh
FORCE_UNSAFE_CONFIGURE=1 CC=wllvm CFLAGS="-O0 -Xclang -disable-O0-optnone -fPIC -fPIE" LDFLAGS="-pie" CXX=wllvm++ CXXFLAGS="-O0 -Xclang -disable-O0-optnone -fPIC -fPIE" ./configure --disable-gcc-warnings
make -j 4
```

##OCCAM

Same as above, except use gclang/gclang++ and option O3 instead of O0, Xclang, disable-O0-optnone


