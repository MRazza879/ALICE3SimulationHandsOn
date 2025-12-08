#!/bin/bash

if [ -z "$O2_ROOT" ]; then
    echo "Error: O2_ROOT environment variable not defined"
    exit 1
fi
echo "O2_ROOT is set to $O2_ROOT"

cd SimulationResults || {
    echo "Error: Failed to change directory to SimulationResults"
    exit 1
}

o2-sim-digitizer-workflow -b --interactionRate 93e3 --configKeyValues="ITSAlpideParam.roFrameLengthInBC=322;"
