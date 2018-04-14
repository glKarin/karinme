#!/bin/sh

INSTALLPATH=/opt/karinme

echo "MicroEmulator Version: 3.0.0-SNAPSHOT.114"
#$INSTALLPATH/script/microemulator_with_fullscreen.sh $*
$*

$INSTALLPATH/bin/karinme
