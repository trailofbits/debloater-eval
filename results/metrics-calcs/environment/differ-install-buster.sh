#!/bin/sh
set -ex
# install differ and all dependencies
sudo apt update
sudo apt install -y git curl
git clone https://github.com/trailofbits/differ.git -b eval
# install python3.9
curl https://pyenv.run | bash
echo 'export PYENV_ROOT="$HOME/.pyenv"' >> ~/.bashrc
echo 'command -v pyenv >/dev/null || export PATH="$PYENV_ROOT/bin:$PATH"' >> ~/.bashrc
echo 'eval "$(pyenv init -)"' >> ~/.bashrc
source ~/.bashrc
sudo apt install -y build-essential libssl-dev zlib1g-dev \
libbz2-dev libreadline-dev libsqlite3-dev curl \
libncursesw5-dev xz-utils tk-dev libxml2-dev libxmlsec1-dev libffi-dev liblzma-dev
pyenv install 3.9.18
pyenv global 3.9.18

sudo apt-get install -y libfuzzy-dev lftp lighttpd memcached \
       tcpdump binutils unzip poppler-utils imagemagick nmap
sudo systemctl stop memcached
sudo systemctl disable memcached
# install pipenv
python3.9 -m pip install --user pipenv
cd differ
# make virtual environment
python3.9 -m pipenv sync --dev
# setup radamsa
./setup-radamsa.sh
cd ..
# install nvm
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.5/install.sh | bash
source ~/.bashrc
nvm install node
# allow current user to execute tcpdump
sudo apt install -y tcpdump
sudo setcap cap_net_raw,cap_net_admin=eip $(sudo which tcpdump)
sudo ln -s /usr/sbin/tcpdump /usr/bin/tcpdump # make tcpdump accessible from user PATH
set +ex
