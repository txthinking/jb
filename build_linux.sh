#!/usr/bin/env bash

curl https://bash.ooo/nami.sh | bash
export PATH=$HOME/.nami/bin:$PATH

nami install jb
nami install 7z
nami install bun
nami install zig

wget https://apt.llvm.org/llvm.sh -O - | sudo bash -s -- 16 all

nami install cmake ninja
sudo apt install cargo ccache git golang libtool pkg-config rustc ruby-full -y

sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt install gcc-11 g++-11 -y
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 100
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 100

if [ $(uname -m) = "aarch64" ]; then
    dir=`pwd`
    cd /tmp/
    git clone https://github.com/ninja-build/ninja
    cd ninja
    ./configure.py --bootstrap
    mv ninja $HOME/.nami/bin/
    cd $dir
    sed -i '138c\require("child_process").execSync(`mkdir -p ${path.dirname(outputPath)}`)' ./src/js/codegen/build-modules.ts
    sed -i '248c\require("child_process").execSync(`mkdir -p ${path.dirname(outputPath)}`)' ./src/js/codegen/build-modules.ts
fi
bun setup
bun run build:release

