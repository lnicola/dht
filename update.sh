#!/bin/bash

while :
do
    FOO=($(./dht 4))
    
    if [ ${#FOO[@]} -eq 2 ]; then
        rrdtool update temperature.rrd N:${FOO[0]}:${FOO[1]}

        sed -i "s/<div id=\"data\">.*<\/div>/<div id=\"data\">${FOO[0]} °C ${FOO[1]}%<\/div>/" temperature.html
    fi

    sleep 30
done
