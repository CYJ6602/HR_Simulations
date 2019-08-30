#!/bin/bash
if [ $# -eq 2 ]
then
    echo "simulating" $2 "events with energy" $1
    sed -e 's/XXXX/'$1'/g' -e 's/YYYY/'$2'/g' < zrbase.mac > input/zr80_$1keV_$2evt_lowlevel.mac
    UCHRArray input/zr80_$1keV_$2evt_lowlevel.mac
    SimCalculate -i data/zr80_$1keV_$2evt_lowlevel.dat -o root/zr80_$1keV_$2evt_lowlevel.root -s zr80ana.set
    Sim_histos -i root/zr80_$1keV_$2evt_lowlevel.root -o hist/zr80_$1keV_$2evt_lowlevel.root
    Gamma_coincidence -i root/zr80_$1keV_$2evt_lowlevel.root -o coin/zr80_$1keV_$2evt_lowlevel.root
    
else
    echo "usage ./sim.sh energy events"
fi
