#!/bin/bash
if [ $# -eq 2 ]
then
    echo "simulating" $2 "events with energy" $1
    sed -e 's/XXXX/'$1'/g' -e 's/YYYY/'$2'/g' < ybase.mac > input/y77_$1keV_$2evt_lowlevel.mac
    UCHRArray input/y77_$1keV_$2evt_lowlevel.mac
    SimCalculate -i data/y77_$1keV_$2evt_lowlevel.dat -o root/y77_$1keV_$2evt_lowlevel.root -s y77ana.set
    Sim_histos -i root/y77_$1keV_$2evt_lowlevel.root -o hist/y77_$1keV_$2evt_lowlevel.root 
else
    echo "usage ./sim.sh energy events"
fi
