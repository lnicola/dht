#!/bin/bash
rrdtool create temperature.rrd --step 30 --start N \
    DS:temperature:GAUGE:60:-10:100 \
    DS:humidity:GAUGE:60:0:100 \
    RRA:AVERAGE:0.5:1:120 \
    RRA:AVERAGE:0.5:1:2880 \
    RRA:AVERAGE:0.5:120:168 \
    RRA:AVERAGE:0.5:120:720 \
    RRA:AVERAGE:0.5:2880:365

