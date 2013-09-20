#!/bin/bash        

INTEMP_COLOR="#CC0000"
OUTTEMP_COLOR="#0000FF"

ARGS="-E --y-grid 0.2:5 --width 1024 --height 768 --vertical-label 'Temperature [C]' --right-axis 2:0 --right-axis-label 'Humidity [%]'
      DEF:temp=temperature.rrd:temperature:AVERAGE
      LINE1:temp$INTEMP_COLOR:'Temperature'
      DEF:humidity=temperature.rrd:humidity:AVERAGE
      CDEF:scaledhumidity=humidity,2,/
      LINE1:scaledhumidity$OUTTEMP_COLOR:'Humidity'"

echo $ARGS | xargs rrdtool graph temp_hourly.png --start -4h
echo $ARGS | xargs rrdtool graph temp_daily.png --start -1d
echo $ARGS | xargs rrdtool graph temp_weekly.png --start -1w
echo $ARGS | xargs rrdtool graph temp_monthly.png --start -1m
echo $ARGS | xargs rrdtool graph temp_yearly.png --start -1y

mv -f temp_hourly.png hourly.png
mv -f temp_daily.png daily.png
mv -f temp_weekly.png weekly.png
mv -f temp_monthly.png monthly.png
mv -f temp_yearly.png yearly.png

