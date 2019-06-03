@echo off
rem @version $Revision: 942 $ ($Author: vlads $)  $Date: 2007-02-17 06:41:16 +0800 (周六, 17 二月 2007) $
title *Jetty:microemu-webstart

call mvn -o -P debug webstart:jnlp
echo Go to http://localhost:8080/microemu-webstart/
call mvn %* jetty:run

title Jetty:microemu-webstart - ended

pause
