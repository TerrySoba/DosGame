#!/bin/bash

# you can find DJGPP for cross compilation from:
#   https://github.com/andrewwutw/build-djgpp
DJGPP_INSTALL_PATH=~/program_sources/djgpp

# setup build environment
pushd ${DJGPP_INSTALL_PATH}
. ./setenv
popd

# now just call make to build
make
