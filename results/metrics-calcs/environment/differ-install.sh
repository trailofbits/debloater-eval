#!/bin/sh
set -ex
# install differ and all dependencies
sudo apt update
sudo apt install -y git curl
git clone https://github.com/trailofbits/differ.git -b eval
# install python
sudo add-apt-repository ppa:deadsnakes/ppa
sudo apt-get install -y python3.9 python3.9-dev python3-pip python3.9-venv libfuzzy-dev lftp lighttpd memcached \
       tcpdump binutils unzip poppler-utils imagemagick nmap
sudo systemctl stop memcached
sudo systemctl disable memcached
# install pipenv
python3.9 -m pip install --user pipenv
cd differ
# make virtual environment
pipenv sync --dev
# setup radamsa
./setup-radamsa.sh
cd ..
# install nvm
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.5/install.sh | bash
source ~/.bashrc
nvm install node
# allow current user to execute tcpdump
sudo apt install -y tcpdump
sudo setcap cap_net_raw,cap_net_admin=eip $(which tcpdump)