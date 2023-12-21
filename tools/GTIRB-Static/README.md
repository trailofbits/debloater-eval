## GTIRB To Static
### Overview
Statically cuts out unreachable libraries and code. Leverages Reachable Reduce.

### Debloat Instructions
1. Pull the pre-built docker image.
```
docker image pull docker.tpcp.io/metis/xform-server@sha256:e0b8c5472be00130fbc54d2f699dd0696be01f7bab504d7729370ec29de66164
```
2. Open a terminal in the image
```
export CON_ID=`docker run -it docker.tpcp.io/metis/xform-server bash`
```
3. Copy target binary into the container
```
docker cp path/to/bin $CON_ID:/root/
```
3. Run the debloat command on a new binary
```
gtirb-to-static target.bin target.reduced.gtirb
```
4. Compile it into a binary using gtirb-pprinter
```
gtirb-pprinter target.reduced.gtirb --binary target.reduce
```

### Example with gzip
1. Open a terminal in the tool's environment
```
docker pull docker.tpcp.io/metis/xform-server
docker run -it docker.tpcp.io/metis/xform-server bash
```
2. Download and build gzip
```
apt update && apt install wget -y
wget https://mirrors.ocf.berkeley.edu/gnu/gzip/gzip-1.12.tar.gz
tar xf gzip-1.12.tar.gz
cd gzip-1.12
FORCE_UNSAFE_CONFIGURE=1 ./configure
make
```
3. Run gtirb-to-static on the built gzip binary
```
gtirb-to-static ./gzip gzip-reduced.bin
```

