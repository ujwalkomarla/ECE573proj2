#!/bin/bash
pkill -TERM p2mpserver
curl http://ipecho.net/plain;echo
cd ProjectTestCases
./script.sh
exit
