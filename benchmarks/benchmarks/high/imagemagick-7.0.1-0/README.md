# Build Instructions

## Trimmer

```
apt install -y autoconf
cd source/ImageMagick
FORCE_UNSAFE_CONFIGURE=1 FORCE_UNSAFE_CONFIGURE=1 CC="wllvm" CXXFLAGS="-fPIC -fPIE" CFLAGS="-O0 -Xclang -disable-O0-optnone -fPIC -fPIE" LDFLAGS="-pie" ./configure
make
```
