#!/bin/bash

set -x

function dexec () {
  docker exec gtirb-to-static "$@"
}

function debloat() {
  benchmark=$1
  binary=$2
  docker container rm -f gtirb-to-static
  docker run -d \
         --network=host \
         --name gtirb-to-static \
         -w /workdir \
         -v $(pwd):/host:rw \
         gtirb-to-static \
         tail -f /dev/null
  dexec /bin/bash -c "cp -r /host/benchmarks/${benchmark}*/binaries/64/* ./"
  dexec /bin/bash -c "LD_LIBRARY_PATH=/workdir timeout 2d /usr/bin/time -q -f %e,%S,%U,%M,%t,%K,%x gtirb-to-static ./$binary ./$binary.reduced" 2>&1 | tee $(basename $benchmark)-gtirb-to-static.log"
  output_dir=./benchmarks-debloated/$benchmark/gtirb-to-static
  mkdir -p $output_dir
  docker cp gtirb-to-static:/workdir/$binary.reduced $output_dir
}


#debloat low/bzip2 bzip2
#debloat low/chown chown
#debloat low/date date
#debloat low/grep grep
#debloat low/gzip gzip
#debloat low/mkdir mkdir
#debloat low/rm rm
#debloat low/sort sort
#debloat low/tar tar
#debloat low/uniq uniq
#
#debloat medium/memcached memcached
#debloat medium/lighttpd lighttpd
#debloat medium/binutils objdump
#debloat medium/bftpd bftpd
#debloat medium/wget wget
#debloat medium/make make

#debloat high/poppler pdftohtml
debloat high/imagemagick magick
#debloat high/nginx nginx
#debloat high/nmap nmap
