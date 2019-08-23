#!/bin/bash
if [ $# -eq 2 ]
then
    echo "simulating" $2 "events with energy" $1
    sed -e 's/XXXX/'$1'/g' -e 's/YYYY/'$2'/g' < mobase.mac > input/mo83_$1keV_$2evt_lowlevel.mac
    UCHRArray input/mo83_$1keV_$2evt_lowlevel.mac
    SimCalculate -i data/mo83_$1keV_$2evt_lowlevel.dat -o root/mo83_$1keV_$2evt_lowlevel.root -s mo83_minos.set
    Sim_histos -i root/mo83_$1keV_$2evt_lowlevel.root -o hist/mo83_$1keV_$2evt_lowlevel.root 
else
    echo "usage ./sim.sh energy events"
fi
