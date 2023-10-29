#!/usr/bin/env bash

curl https://bash.ooo/nami.sh | bash
export PATH=$HOME/.nami/bin:$PATH

nami install 7z
nami install bun
nami install jb
nami install zigup
zigup 0.12.0-dev.899+027aabf49

brew install llvm@16
export PATH="$PATH:$(brew --prefix llvm@16)/bin"
export LDFLAGS="$LDFLAGS -L$(brew --prefix llvm@16)/lib"
export CPPFLAGS="$CPPFLAGS -I$(brew --prefix llvm@16)/include"
brew install automake ccache cmake coreutils esbuild gnu-sed go libiconv libtool ninja pkg-config rust
bun install
make setup
make release-bindings -j12
make release
