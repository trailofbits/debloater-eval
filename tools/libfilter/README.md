## LibFilter (Nibbler)
### Overview
Uses static analysis to identify unused function calls in a program and its shared libraries. It then cuts these out creating a debloated binary that it relinks to local, trimmed copies of the libraries it uses, so that the debloated binary can still be dynamically linked and debloated without modifying system libraries other binaries may depend on.

### Debloat Instructions
2. Open a shell into a container started with the LibFilter image `docker run --rm -it registry.gitlab.com/egalito/libfilter/ubuntu20_eval:latest@sha256:3f0968361e6e51b2354fd036787ecd4a75617ef052ea8109d0d5a412fcb699cc`
3. (If necessary) Build the target binary
4. Run libfilter_main on the target binary `/libfilter/app/libfilter_main <path to bin>`
5. The binary will be replaced by a debloated version that is linked to trimmed down libraries copied into a new sibling directory.

### Example with gzip
1. Open a terminal in the tool's environment
```
docker run --rm -it ubuntu20_eval:latest
```
2. Download and build gzip
```
mkdir /app && cd /app
wget https://mirrors.ocf.berkeley.edu/gnu/gzip/gzip-1.12.tar.gz
tar xf gzip-1.12.tar.gz
cd gzip-1.12
FORCE_UNSAFE_CONFIGURE=1 ./configure
make
```
3. Run LibFilter on the built gzip binary
```
/libfilter/app/libfilter_main /app/gzip-1.12/gzip
```