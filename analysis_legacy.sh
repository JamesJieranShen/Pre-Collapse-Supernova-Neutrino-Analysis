#!/bin/bash
# Sets snowglobes envrionemnt variable to the correct version, and reverts it back after it is done.
legacy_snowglobes=/home/james/Shared/neutrino/snowglobes_legacy

sys_snowglobes = $SNOWGLOBES
export SNOWGLOBES=$legacy_snowglobes

make all
cd bin
./analysis

export SNOWGLOBES=$sys_snowglobes
