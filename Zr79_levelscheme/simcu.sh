#!/bin/bash
if [ $# -eq 2 ]
then
    echo "simulating" $2 "events with energy" $1
    sed -e 's/XXXX/'$1'/g' -e 's/YYYY/'$2'/g' < zrbase.mac > input/zr79_$1keV_$2evt_lowlevel.mac
    UCHRArray input/zr79_$1keV_$2evt_lowlevel.mac
    SimCalculate -i data/zr79_$1keV_$2evt_lowlevel.dat -o root/zr79_$1keV_$2evt_lowlevel.root -s zr79ana.set
    Sim_histos -i root/zr79_$1keV_$2evt_lowlevel.root -o hist/zr79_$1keV_$2evt_lowlevel.root 
else
    echo "usage ./sim.sh energy events"
fi
