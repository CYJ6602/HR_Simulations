if [ $# -eq 3 ]
then
    echo "simulating" $3 "events with energy" $1 " and tau " $2
    sed -e 's/EEEE/'$1'/g' -e 's/NNNN/'$3'/g' -e 's/TTTT/'$2'/g' < MBbase.mac > MBcoords/zr80_$1keV_$2ps_$3evt.mac
    sed -e 's/EEEE/'$1'/g' -e 's/TTTT/'$2'/g' < base.lvldata > MBcoords/zr80_$1keV_$2ps.lvldata
    UCHiCARI MBcoords/zr80_$1keV_$2ps_$3evt.mac
    SimCalculate -i MBcoords/zr80_$1keV_$2ps_$3evt.dat -o MBcoords/zr80_$1keV_$2ps_$3evt_cal.dat -s zr80ana.set 
    Sim_histos -i MBcoords/zr80_$1keV_$2ps_$3evt_cal.dat -o MBcoords/zr80_$1keV_$2ps_$3evt_hist.dat
else
    echo "usage ./sim_MBcoords.sh energy tau events"
fi
