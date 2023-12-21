#!/bin/bash
# eval_runs_buster 1-10
timeout 12h pipenv run differ -r reports-buster --verbose samples/lighttpd/eval-buster.yml 2>&1 | tee reports-buster/lighttpd-eval-buster.log
timeout 12h pipenv run differ -r reports-buster --verbose samples/grep-2.19/eval-buster.yml 2>&1 | tee reports-buster/grep-eval-buster.log
timeout 12h pipenv run differ -r reports-buster --verbose samples/mkdir-5.2.1/eval-buster.yml 2>&1 | tee reports-buster/mkdir-eval-buster.log
timeout 12h pipenv run differ -r reports-buster --verbose samples/gzip-1.2.4/eval-buster.yml 2>&1 | tee reports-buster/gzip-eval-buster.log
timeout 12h pipenv run differ -r reports-buster --verbose samples/rm-8.4/eval-buster.yml 2>&1 | tee reports-buster/rm-eval-buster.log
timeout 12h pipenv run differ -r reports-buster --verbose samples/wget/eval-buster.yml 2>&1 | tee reports-buster/wget-eval-buster.log
timeout 12h pipenv run differ -r reports-buster --verbose samples/memcached/eval-buster.yml 2>&1 | tee reports-buster/memcached-eval-buster.log
timeout 12h pipenv run differ -r reports-buster --verbose samples/tar-1.14/eval-buster.yml 2>&1 | tee reports-buster/tar-eval-buster.log
timeout 12h pipenv run differ -r reports-buster --verbose samples/bzip2-1.0.5/eval-buster.yml 2>&1 | tee reports-buster/bzip2-eval-buster.log
timeout 12h pipenv run differ -r reports-buster --verbose samples/nginx/eval-buster.yml 2>&1 | tee reports-buster/nginx-eval-buster.log
