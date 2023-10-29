#!/usr/bin/env bash

curl https://bash.ooo/nami.sh | bash
export PATH=$HOME/.nami/bin:$PATH

nami install 7z
nami install bun
nami install jb
nami install zigup
zigup 0.12.0-dev.899+027aabf49

wget https://apt.llvm.org/llvm.sh -O - | sudo bash -s -- 16 all
curl -fsSL https://esbuild.github.io/dl/latest | bash
chmod +x ./esbuild
mv ./esbuild $HOME/.nami/bin/
sudo apt install cargo ccache cmake git golang libtool ninja-build pkg-config rustc -y
bun install
if [ $(uname -m) = "aarch64" ]; then
    sed -i '162c\require("child_process").execSync(`mkdir -p ${path.dirname(outputPath)}`)' ./src/js/_codegen/build-modules.ts
    sed -i '258c\require("child_process").execSync(`mkdir -p ${path.dirname(outputPath)}`)' ./src/js/_codegen/build-modules.ts
fi

sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt install gcc-11 g++-11 -y
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 100
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 100

make setup
make release-bindings -j12

sudo apt-get update
sudo apt-get install -y ca-certificates curl gnupg
sudo mkdir -p /etc/apt/keyrings
curl -fsSL https://deb.nodesource.com/gpgkey/nodesource-repo.gpg.key | sudo gpg --dearmor -o /etc/apt/keyrings/nodesource.gpg
export NODE_MAJOR=20
echo "deb [signed-by=/etc/apt/keyrings/nodesource.gpg] https://deb.nodesource.com/node_$NODE_MAJOR.x nodistro main" | sudo tee /etc/apt/sources.list.d/nodesource.list
sudo apt-get update
sudo apt-get install nodejs -y

make release
