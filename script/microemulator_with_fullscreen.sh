#!/bin/sh

INSTALLPATH=/opt/karinme
WMCTRL=/usr/bin/wmctrl

echo "MicroEmulator Version: 3.0.0-SNAPSHOT.114"

if [ -x $WMCTRL ]; then
	echo "Waiting make fullscreen by wmctrl"
	$INSTALLPATH/script/wmctrl_scan_window.sh "MicroEmulator" &
else
	echo "Can not find wmctrl in \$PATH"
fi

$*

if [ "x$?" != "x0" ]; then
	echo "kill window name scan process"
	echo `ps | grep \{wmctrl_scan_win}`
	kill `ps | grep \{wmctrl_scan_win} | cut -d ' ' -f 2`
fi
