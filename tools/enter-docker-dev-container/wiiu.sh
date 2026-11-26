#!/bin/bash -ex

# This script assumes that Docker is installed.
# Enters the devkitPPC environment used to build the Wii U port.

if [ $# -eq 0 ]; then
    docker run -it --rm -v $(pwd):/mnt -w /mnt devkitpro/devkitppc:latest
else
    docker run --rm -v $(pwd):/mnt -w /mnt devkitpro/devkitppc:latest "$@"
fi
