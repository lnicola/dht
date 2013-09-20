#!/bin/bash

while :
do
    FOO=($(./dht 4))
    
    if [ ${#FOO[@]} -eq 2 ]; then
        rrdtool update temperature.rrd N:${FOO[0]}:${FOO[1]}
    fi

    sleep 5
done
