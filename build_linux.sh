#!/usr/bin/env bash

curl https://bash.ooo/nami.sh | bash
export PATH=$HOME/.nami/bin:$PATH

nami install 7z
nami install bun
nami install jb
nami install zigup
zigup 0.12.0-dev.899+027aabf49

wget https://apt.llvm.org/llvm.sh -O - | sudo bash -s -- 16 all
sudo apt install cargo ccache cmake git golang libtool ninja-build pkg-config rustc esbuild -y
bun install
if [ $(uname -m) = "aarch64" ]; then
    sed -i '162c\require("child_process").execSync(`mkdir -p ${path.dirname(outputPath)}`)' ./src/js/_codegen/build-modules.ts
    sed -i '258c\require("child_process").execSync(`mkdir -p ${path.dirname(outputPath)}`)' ./src/js/_codegen/build-modules.ts
fi
make setup
make release-bindings -j12
make release
