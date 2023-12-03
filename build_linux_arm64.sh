#!/usr/bin/env bash

curl https://bash.ooo/nami.sh | bash
export PATH=$HOME/.nami/bin:$PATH

nami install jb 7z bun zig go cmake

if [ $(uname -m) = "aarch64" ]; then
    sudo apt update
    sudo apt install gcc g++ -y
    dir=`pwd`
    cd /tmp/
    git clone https://github.com/ninja-build/ninja
    cd ninja
    ./configure.py --bootstrap
    mv ninja $HOME/.nami/bin/
    cd $dir
fi

wget https://apt.llvm.org/llvm.sh -O - | sudo bash -s -- 16 all

sudo apt install cargo ccache git libtool pkg-config rustc ruby-full xz-utils make -y

sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt install gcc-11 g++-11 -y
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 100
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 100

bun setup
bun run build:release

