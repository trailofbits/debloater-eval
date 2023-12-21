#!/bin/bash
# Note: should run with bash to contain environment variable changes
set -x
mkdir -p reports-rd3 reports-aggressive-rd3
LD_LIBRARY_PATH="/home/metis2/differ/debloater-eval.batch2/debloater-eval-binaries/benchmarks/high/poppler-0.60/binaries/64/"
LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/home/metis2/differ/debloater-eval.batch2/debloater-eval-binaries/benchmarks/high/imagemagick-7.0.1-0/binaries/64"
LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/home/metis2/bionic-libs/manual"
LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/home/metis2/xenial-libs/manual"
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/home/metis2/fossa-libs/manual"
# necessary for magick to find colors.xml and magic.xml config files
export MAGICK_CONFIGURE_PATH="/etc/ImageMagick-6/"
echo "Checking that libraries are present for all campaigns"
ldd_standard="$(python3 /home/metis2/metis-eval-private/scripts/ldd-check.py eval.yml -v 2>&1 | grep 'missing library')"
if [[ -n $ldd_standard ]]; then 
    echo "Libraries missing for standard campaigns: $ldd_standard"
    exit 1
fi
ldd_aggressive=$(python3 /home/metis2/metis-eval-private/scripts/ldd-check.py eval-aggressive.yml -v 2>&1 | grep "missing library")
if [[ -n $ldd_aggressive ]]; then 
    echo "Libraries missing for aggressive campaigns: $ldd_aggressive"
    exit 1 
fi
echo "All libraries present"
set -e
# standard runs
timeout 12h pipenv run differ -r reports-rd3 --verbose samples/lighttpd/eval.yml 2>&1 | tee reports-rd3/lighttpd-eval.log
timeout 12h pipenv run differ -r reports-rd3 --verbose samples/grep-2.19/eval.yml 2>&1 | tee reports-rd3/grep-eval.log
timeout 12h pipenv run differ -r reports-rd3 --verbose samples/mkdir-5.2.1/eval.yml 2>&1 | tee reports-rd3/mkdir-eval.log
timeout 12h pipenv run differ -r reports-rd3 --verbose samples/gzip-1.2.4/eval.yml 2>&1 | tee reports-rd3/gzip-eval.log
timeout 12h pipenv run differ -r reports-rd3 --verbose samples/rm-8.4/eval.yml 2>&1 | tee reports-rd3/rm-eval.log
timeout 12h pipenv run differ -r reports-rd3 --verbose samples/wget/eval.yml 2>&1 | tee reports-rd3/wget-eval.log
timeout 12h pipenv run differ -r reports-rd3 --verbose samples/memcached/eval.yml 2>&1 | tee reports-rd3/memcached-eval.log
# ran manually
#timeout 12h pipenv run differ -r reports-rd3 --verbose samples/tar-1.14/eval.yml 2>&1 | tee reports-rd3/tar-eval.log
timeout 12h pipenv run differ -r reports-rd3 --verbose samples/bzip2-1.0.5/eval.yml 2>&1 | tee reports-rd3/bzip2-eval.log
timeout 12h pipenv run differ -r reports-rd3 --verbose samples/nginx/eval.yml 2>&1 | tee reports-rd3/nginx-eval.log
timeout 12h pipenv run differ -r reports-rd3 --verbose samples/uniq-8.16/eval.yml 2>&1 | tee reports-rd3/uniq-eval.log
timeout 12h pipenv run differ -r reports-rd3 --verbose samples/date-8.21/eval.yml 2>&1 | tee reports-rd3/date-eval.log
timeout 12h pipenv run differ -r reports-rd3 --verbose samples/bftpd-6.1/eval.yml 2>&1 | tee reports-rd3/bftpd-eval.log
timeout 12h pipenv run differ -r reports-rd3 --verbose samples/make/eval.yml 2>&1 | tee reports-rd3/make-eval.log
timeout 12h pipenv run differ -r reports-rd3 --verbose samples/imagemagick/eval.yml 2>&1 | tee reports-rd3/imagemagick-eval.log
timeout 12h pipenv run differ -r reports-rd3 --verbose samples/pdftohtml/eval.yml 2>&1 | tee reports-rd3/pdftohtml-eval.log
timeout 12h pipenv run differ -r reports-rd3 --verbose samples/sort-8.16/eval.yml 2>&1 | tee reports-rd3/sort-eval.log
timeout 12h pipenv run differ -r reports-rd3 --verbose samples/chown-8.2/eval.yml 2>&1 | tee reports-rd3/chown-eval.log
timeout 12h pipenv run differ -r reports-rd3 --verbose samples/objdump/eval.yml 2>&1 | tee reports-rd3/objdump-eval.log
timeout 12h pipenv run differ -r reports-rd3 --verbose samples/nmap/eval.yml 2>&1 | tee reports-rd3/nmap-eval.log
# aggressive runs
timeout 12h pipenv run differ -r reports-aggressive-rd3 --verbose samples/lighttpd/eval-aggressive.yml 2>&1 | tee reports-rd3/lighttpd-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive-rd3 --verbose samples/grep-2.19/eval-aggressive.yml 2>&1 | tee reports-rd3/grep-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive-rd3 --verbose samples/mkdir-5.2.1/eval-aggressive.yml 2>&1 | tee reports-rd3/mkdir-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive-rd3 --verbose samples/gzip-1.2.4/eval-aggressive.yml 2>&1 | tee reports-rd3/gzip-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive-rd3 --verbose samples/rm-8.4/eval-aggressive.yml 2>&1 | tee reports-rd3/rm-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive-rd3 --verbose samples/wget/eval-aggressive.yml 2>&1 | tee reports-rd3/wget-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive-rd3 --verbose samples/memcached/eval-aggressive.yml 2>&1 | tee reports-rd3/memcached-eval-aggressive.log
# skipping
#timeout 12h pipenv run differ -r reports-aggressive-rd3 --verbose samples/tar-1.14/eval-aggressive.yml 2>&1 | tee reports-rd3/tar-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive-rd3 --verbose samples/bzip2-1.0.5/eval-aggressive.yml 2>&1 | tee reports-rd3/bzip2-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive-rd3 --verbose samples/nginx/eval-aggressive.yml 2>&1 | tee reports-rd3/nginx-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive-rd3 --verbose samples/uniq-8.16/eval-aggressive.yml 2>&1 | tee reports-rd3/uniq-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive-rd3 --verbose samples/date-8.21/eval-aggressive.yml 2>&1 | tee reports-rd3/date-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive-rd3 --verbose samples/bftpd-6.1/eval-aggressive.yml 2>&1 | tee reports-rd3/bftpd-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive-rd3 --verbose samples/make/eval-aggressive.yml 2>&1 | tee reports-rd3/make-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive-rd3 --verbose samples/imagemagick/eval-aggressive.yml 2>&1 | tee reports-rd3/imagemagick-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive-rd3 --verbose samples/pdftohtml/eval-aggressive.yml 2>&1 | tee reports-rd3/pdftohtml-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive-rd3 --verbose samples/sort-8.16/eval-aggressive.yml 2>&1 | tee reports-rd3/sort-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive-rd3 --verbose samples/chown-8.2/eval-aggressive.yml 2>&1 | tee reports-rd3/chown-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive-rd3 --verbose samples/objdump/eval-aggressive.yml 2>&1 | tee reports-rd3/objdump-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive-rd3 --verbose samples/nmap/eval-aggressive.yml 2>&1 | tee reports-rd3/nmap-eval-aggressive.log
