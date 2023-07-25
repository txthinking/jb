#!/bin/bash

if [ $# -ne 1 ]; then
    echo "./build.sh version"
    exit
fi

mkdir _

docker run --rm dockcross/linux-x64 > cross
chmod +x cross
./cross bash -c 'curl https://bash.ooo/nami.sh | bash; export PATH=$PATH:$HOME/.nami/bin; nami install 7z bun; bun build ./main.js --compile'
mv main _/jb_linux_amd64
docker run --rm dockcross/linux-arm64 > cross
chmod +x cross
./cross bash -c 'curl https://bash.ooo/nami.sh | bash; export PATH=$PATH:$HOME/.nami/bin; nami install 7z bun; bun build ./main.js --compile'
mv main _/jb_linux_arm64

chmod +x _/jb_linux_amd64
./_/jb_linux_amd64 'cp("https://github.com/oven-sh/bun/releases/latest/download/bun-linux-x64-baseline.zip", "bun-linux-x64-baseline/bun", "/tmp/bun")'
chmod +x /tmp/bun
/tmp/bun build ./main.js --compile
mv main _/jb_linux_amd64-baseline

nami release github.com/txthinking/jb $1 _

rm -rf _
