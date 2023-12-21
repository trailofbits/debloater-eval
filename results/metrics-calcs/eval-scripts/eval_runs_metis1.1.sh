#!/bin/bash
set -e
# eval.yml
# note these are not consecutive bc grep and wget were skipped in eval_runs_metis1.sh
timeout 12h pipenv run differ --verbose samples/grep-2.19/eval.yml 2>&1 | tee reports/grep-eval.log
timeout 12h pipenv run differ --verbose samples/wget/eval.yml 2>&1 | tee reports/wget-eval.log
timeout 12h pipenv run differ --verbose samples/bftpd-6.1/eval.yml 2>&1 | tee reports/bftpd-eval.log
timeout 12h pipenv run differ --verbose samples/make/eval.yml 2>&1 | tee reports/make-eval.log
timeout 12h pipenv run differ --verbose samples/imagemagick/eval.yml 2>&1 | tee reports/imagemagick-eval.log
# eval-aggressive.yml
# 1-10
timeout 12h pipenv run differ -r reports-aggressive --verbose samples/lighttpd/eval-aggressive.yml 2>&1 | tee reports/lighttpd-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive --verbose samples/grep-2.19/eval-aggressive.yml 2>&1 | tee reports/grep-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive --verbose samples/mkdir-5.2.1/eval-aggressive.yml 2>&1 | tee reports/mkdir-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive --verbose samples/gzip-1.2.4/eval-aggressive.yml 2>&1 | tee reports/gzip-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive --verbose samples/rm-8.4/eval-aggressive.yml 2>&1 | tee reports/rm-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive --verbose samples/wget/eval-aggressive.yml 2>&1 | tee reports/wget-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive --verbose samples/memcached/eval-aggressive.yml 2>&1 | tee reports/memcached-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive --verbose samples/tar-1.14/eval-aggressive.yml 2>&1 | tee reports/tar-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive --verbose samples/bzip2-1.0.5/eval-aggressive.yml 2>&1 | tee reports/bzip2-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive --verbose samples/nginx/eval-aggressive.yml 2>&1 | tee reports/nginx-eval-aggressive.log
