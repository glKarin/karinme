#!/bin/sh

WMCTRL=/usr/bin/wmctrl
LOOP=c
TIMEOUT=+++++++++++++++

if [ ! -x $WMCTRL ]; then
	echo "Need wmctrl support, and can not find wmctrl in \$PATH"
	exit 1
fi

if [ "x$1" = "x" ]; then
	echo "Need a argument for scaning window name"
	$WMCTRL -l
	exit 2
else
	while [ -z `wmctrl -l | grep $1` ]
	do
		if [ "$LOOP" = "c$TIMEOUT" ]; then
			echo "Scan window name: \"$1\" time out(15s). Exiting"
			exit 3
		else
			LOOP=$LOOP+
			echo "Not find window name: \"$1\", waiting 1 second for next scaning"
			#echo $LOOP
			sleep 1
		fi
	done
	#make MicroEmulator full screen by wmctrl in Harmattan UI
	echo "Find window name: \"$1\", execute $WMCTRL -r $1 -b add,fullscreen"
	$WMCTRL -r $1 -b add,fullscreen
fi
