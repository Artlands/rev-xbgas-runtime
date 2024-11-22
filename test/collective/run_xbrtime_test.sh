#!/bin/bash

#Build the test
make

# Check that the exec was built...
if [[ -x $RVASM.exe ]]; then
	sst "--model-options=$RVASM.exe 2" ./rev-xbrtime-test.py
else
	echo "Test $RVASM ASM: File not found - likely build failed"
	exit 1
fi