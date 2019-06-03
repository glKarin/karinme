@echo off
rem @version $Revision: 700 $ ($Author: vlads $)  $Date: 2007-02-12 03:32:44 +0800 (周一, 12 二月 2007) $
title *Jetty:bytecode-webstart

call mvn -P debug webstart:jnlp

echo Go to http://localhost:8080/bytecode-webstart/

call mvn %* jetty:run

title Jetty:bytecode-webstart - ended

pause
