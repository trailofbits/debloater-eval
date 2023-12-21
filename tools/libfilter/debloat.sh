#!/bin/bash
set -x

function dexec () {
  docker exec libfilter "$@"
}

function debloat() {
  benchmark=$1
  binary=$2
  docker container rm -f libfilter
  docker run -d \
         --network=host \
         --name libfilter \
         -v $(pwd):/host:rw \
         libfilter \
         tail -f /dev/null
  dexec /bin/bash -c "cp -r /host/benchmarks/${benchmark}*/binaries/64/* ./"
  dexec /usr/bin/time -q -f %e,%S,%U,%M,%t,%K,%x ./app/libfilter_main ./$binary
  output_dir=benchmarks-debloated/$benchmark/libfilter/
  mkdir -p $output_dir
  docker cp libfilter:/usr/src/libfilter/$binary $output_dir/$binary
  docker cp libfilter:/usr/src/libfilter/_libfilter $output_dir/_libfilter
}

debloat low/bzip2 bzip2
debloat low/chown chown
debloat low/date date
debloat low/grep grep
debloat low/gzip gzip
debloat low/mkdir mkdir
debloat low/rm rm
debloat low/sort sort
debloat low/tar tar
debloat low/uniq uniq

debloat medium/memcached memcached
debloat medium/lighttpd lighttpd
debloat medium/binutils objdump
debloat medium/bftpd bftpd
debloat medium/wget wget
debloat medium/make make

debloat high/poppler pdftohtml
debloat high/imagemagick magick
debloat high/nginx nginx
debloat high/nmap nmap
