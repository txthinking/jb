#!/usr/bin/env bash

curl https://bash.ooo/nami.sh | bash
export PATH=$HOME/.nami/bin:$PATH

nami install jb 7z bun zig go

brew install llvm@16
export PATH="$(brew --prefix llvm@16)/bin:$PATH"
export LDFLAGS="$LDFLAGS -L$(brew --prefix llvm@16)/lib"
export CPPFLAGS="$CPPFLAGS -I$(brew --prefix llvm@16)/include"

brew install automake ccache cmake coreutils gnu-sed libiconv libtool ninja pkg-config rust

bun setup
bun run build:release
