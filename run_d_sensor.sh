#!/bin/bash

D_SENSOR=.00665
VARIATION=.0002
STEPS=20
D_S=$(echo "$D_SENSOR-($STEPS/2.*$VARIATION)" | bc)
OUTFILE=""

for (( i = 0; i < $STEPS; i++ )); do
  OUTFILE="d_sensor_variation/out${D_S}.dat"
  ./simple_diffraction 300e-6 1e-3 100001 200 85e-5 $D_S 15e-3 $OUTFILE
  D_S=$(echo "$D_S+($VARIATION)" | bc)
done




