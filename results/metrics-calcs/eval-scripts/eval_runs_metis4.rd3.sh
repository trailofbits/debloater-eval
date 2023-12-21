#!/bin/bash
# Note: should run with bash to contain environment variable changes
set -x
mkdir -p reports-buster-rd3
export LD_LIBRARY_PATH="/home/metis4/differ/debloater-eval.batch2/debloater-eval-binaries/benchmarks/high/poppler-0.60/binaries/buster/"
echo "Checking that libraries are present for all buster campaigns"
ldd_standard="$(python3 /home/metis4/metis-eval-private/scripts/ldd-check.py eval-buster.yml -v 2>&1 | grep 'missing library')"
if [[ -n $ldd_standard ]]; then 
    echo "Libraries missing for buster campaigns: $ldd_standard"
    exit 1
fi
echo "All libraries present"
set -e
# buster
timeout 12h pipenv run differ -r reports-buster-rd3 --verbose samples/lighttpd/eval-buster.yml 2>&1 | tee reports-buster-rd3/lighttpd-eval-buster.log
timeout 12h pipenv run differ -r reports-buster-rd3 --verbose samples/grep-2.19/eval-buster.yml 2>&1 | tee reports-buster-rd3/grep-eval-buster.log
timeout 12h pipenv run differ -r reports-buster-rd3 --verbose samples/mkdir-5.2.1/eval-buster.yml 2>&1 | tee reports-buster-rd3/mkdir-eval-buster.log
timeout 12h pipenv run differ -r reports-buster-rd3 --verbose samples/gzip-1.2.4/eval-buster.yml 2>&1 | tee reports-buster-rd3/gzip-eval-buster.log
timeout 12h pipenv run differ -r reports-buster-rd3 --verbose samples/rm-8.4/eval-buster.yml 2>&1 | tee reports-buster-rd3/rm-eval-buster.log
timeout 12h pipenv run differ -r reports-buster-rd3 --verbose samples/wget/eval-buster.yml 2>&1 | tee reports-buster-rd3/wget-eval-buster.log
timeout 12h pipenv run differ -r reports-buster-rd3 --verbose samples/memcached/eval-buster.yml 2>&1 | tee reports-buster-rd3/memcached-eval-buster.log
# skipping
#timeout 12h pipenv run differ -r reports-buster-rd3 --verbose samples/tar-1.14/eval-buster.yml 2>&1 | tee reports-buster-rd3/tar-eval-buster.log
timeout 12h pipenv run differ -r reports-buster-rd3 --verbose samples/bzip2-1.0.5/eval-buster.yml 2>&1 | tee reports-buster-rd3/bzip2-eval-buster.log
timeout 12h pipenv run differ -r reports-buster-rd3 --verbose samples/nginx/eval-buster.yml 2>&1 | tee reports-buster-rd3/nginx-eval-buster.log
timeout 12h pipenv run differ -r reports-buster-rd3 --verbose samples/uniq-8.16/eval-buster.yml 2>&1 | tee reports-buster-rd3/uniq-eval-buster.log
timeout 12h pipenv run differ -r reports-buster-rd3 --verbose samples/date-8.21/eval-buster.yml 2>&1 | tee reports-buster-rd3/date-eval-buster.log
timeout 12h pipenv run differ -r reports-buster-rd3 --verbose samples/bftpd-6.1/eval-buster.yml 2>&1 | tee reports-buster-rd3/bftpd-eval-buster.log
timeout 12h pipenv run differ -r reports-buster-rd3 --verbose samples/make/eval-buster.yml 2>&1 | tee reports-buster-rd3/make-eval-buster.log
timeout 12h pipenv run differ -r reports-buster-rd3 --verbose samples/pdftohtml/eval-buster.yml 2>&1 | tee reports-buster-rd3/pdftohtml-eval-buster.log
timeout 12h pipenv run differ -r reports-buster-rd3 --verbose samples/sort-8.16/eval-buster.yml 2>&1 | tee reports-buster-rd3/sort-eval-buster.log
timeout 12h pipenv run differ -r reports-buster-rd3 --verbose samples/chown-8.2/eval-buster.yml 2>&1 | tee reports-buster-rd3/chown-eval-buster.log
timeout 12h pipenv run differ -r reports-buster-rd3 --verbose samples/objdump/eval-buster.yml 2>&1 | tee reports-buster-rd3/objdump-eval-buster.log
timeout 12h pipenv run differ -r reports-buster-rd3 --verbose samples/nmap/eval-buster.yml 2>&1 | tee reports-buster-rd3/nmap-eval-buster.log
