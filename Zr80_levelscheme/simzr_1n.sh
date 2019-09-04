#!/bin/bash
if [ $# -eq 2 ]
then
    echo "simulating" $2 "events with energy" $1
    sed -e 's/XXXX/'$1'/g' -e 's/YYYY/'$2'/g' < zrbase_1n.mac > input/zr80_$1keV_$2evt_lowlevel_1n.mac
    UCHiCARI input/zr80_$1keV_$2evt_lowlevel_1n.mac
    SimCalculate -i data/zr80_$1keV_$2evt_lowlevel_1n.dat -o root/zr80_$1keV_$2evt_lowlevel_1n.root -s zr80ana_1n.set
    Sim_histos -i root/zr80_$1keV_$2evt_lowlevel_1n.root -o hist/zr80_$1keV_$2evt_lowlevel_1n.root
    Gamma_coincidence -i root/zr80_$1keV_$2evt_lowlevel_1n.root -o coin/zr80_$1keV_$2evt_lowlevel_1n.root
  
else
    echo "usage ./simzr_1n.sh energy events"
fi
