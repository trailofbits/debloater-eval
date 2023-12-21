#!/bin/bash
set -e
timeout 12h pipenv run differ --verbose samples/lighttpd/eval.yml 2>&1 | tee reports/lighttpd-eval.log
#timeout 12h pipenv run differ --verbose samples/grep-2.19/eval.yml 2>&1 | tee reports/grep-eval.log
timeout 12h pipenv run differ --verbose samples/mkdir-5.2.1/eval.yml 2>&1 | tee reports/mkdir-eval.log
timeout 12h pipenv run differ --verbose samples/gzip-1.2.4/eval.yml 2>&1 | tee reports/gzip-eval.log
timeout 12h pipenv run differ --verbose samples/rm-8.4/eval.yml 2>&1 | tee reports/rm-eval.log
#timeout 12h pipenv run differ --verbose samples/wget/eval.yml 2>&1 | tee reports/wget-eval.log
timeout 12h pipenv run differ --verbose samples/memcached/eval.yml 2>&1 | tee reports/memcached-eval.log
