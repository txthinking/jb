#!/bin/bash

if [ $# -ne 1 ]; then
    echo "./build.sh version"
    exit
fi

mkdir _

bun build main.js --compile --outfile _/jb

nami release github.com/txthinking/jb $1 _

rm -rf _
