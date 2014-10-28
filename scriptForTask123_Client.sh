#!/bin/bash
make -f makefileClient.c
sleep 1
#Open port numbers 61001-61005,62001-62010,63001-63010 on servers
#Client will be at Lab, $Server0 is my IP(174.97.168.75), $Server1 is Shruti's IP(), $Server2 is system at Lab().
Server0=174.97.168.75
Server1=
Server2=
gnome-terminal -t cTask1_1 -e "time ./p2mpclient $Server0 61001 Task1_1.txt 500"
gnome-terminal -t cTask1_2 -e "time ./p2mpclient $Server0 $Server1 61002 Task1_2.txt 500"
gnome-terminal -t cTask1_3 -e "time ./p2mpclient $Server0 $Server1 $Server2 61003 Task1_3.txt 500"
#gnome-terminal -t cTask1_4 -e "time ./p2mpclient $Server0 $Server1 $Server2 $Server3 61004 Task1_4.txt 500"
#gnome-terminal -t cTask1_5 -e "time ./p2mpclient $Server0 $Server1 $Server2 $Server3 $Server4 61005 Task1_5.txt 500"




gnome-terminal -t cTask2_100 -e "time ./p2mpclient $Server0 $Server1 $Server2 62001 Task2_100.txt 100"
gnome-terminal -t cTask2_200 -e "time ./p2mpclient $Server0 $Server1 $Server2 62002 Task2_200.txt 200"
gnome-terminal -t cTask2_300 -e "time ./p2mpclient $Server0 $Server1 $Server2 62003 Task2_300.txt 300"
gnome-terminal -t cTask2_400 -e "time ./p2mpclient $Server0 $Server1 $Server2 62004 Task2_400.txt 400"
gnome-terminal -t cTask2_500 -e "time ./p2mpclient $Server0 $Server1 $Server2 62005 Task2_500.txt 500"
gnome-terminal -t cTask2_600 -e "time ./p2mpclient $Server0 $Server1 $Server2 62006 Task2_600.txt 600"
gnome-terminal -t cTask2_700 -e "time ./p2mpclient $Server0 $Server1 $Server2 62007 Task2_700.txt 700"
gnome-terminal -t cTask2_800 -e "time ./p2mpclient $Server0 $Server1 $Server2 62008 Task2_800.txt 800"
gnome-terminal -t cTask2_900 -e "time ./p2mpclient $Server0 $Server1 $Server2 62009 Task2_900.txt 900"
gnome-terminal -t cTask2_1000 -e "time ./p2mpclient $Server0 $Server1 $Server2 62010 Task2_1000.txt 1000"




gnome-terminal -t cTask3_01 -e "time ./p2mpclient $Server0 $Server1 $Server2 63001 Task3_01.txt 500"
gnome-terminal -t cTask3_02 -e "time ./p2mpclient $Server0 $Server1 $Server2 63002 Task3_02.txt 500"
gnome-terminal -t cTask3_03 -e "time ./p2mpclient $Server0 $Server1 $Server2 63003 Task3_03.txt 500"
gnome-terminal -t cTask3_04 -e "time ./p2mpclient $Server0 $Server1 $Server2 63004 Task3_04.txt 500"
gnome-terminal -t cTask3_05 -e "time ./p2mpclient $Server0 $Server1 $Server2 63005 Task3_05.txt 500"
gnome-terminal -t cTask3_06 -e "time ./p2mpclient $Server0 $Server1 $Server2 63006 Task3_06.txt 500"
gnome-terminal -t cTask3_07 -e "time ./p2mpclient $Server0 $Server1 $Server2 63007 Task3_07.txt 500"
gnome-terminal -t cTask3_08 -e "time ./p2mpclient $Server0 $Server1 $Server2 63008 Task3_08.txt 500"
gnome-terminal -t cTask3_09 -e "time ./p2mpclient $Server0 $Server1 $Server2 63009 Task3_09.txt 500"
gnome-terminal -t cTask3_10 -e "time ./p2mpclient $Server0 $Server1 $Server2 63010 Task3_10.txt 500"
