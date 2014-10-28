#!/bin/bash
make -f makefileClient.c
sleep 1
#Open port numbers 61001-61005,62001-62010,63001-63010 on servers
#Client will be at Lab, $Server0 is my IP(174.97.168.75), $Server1 is Shruti's IP(), $Server2 is system at Lab().

#dd if=/dev/urandom of=random.txt bs=1M count=1
#gnome-terminal -t Task -e "bash -c \"time ./p2mpclient 127.0.0.1 65423 random.txt 500; echo task; exec bash\""
dd if=/dev/urandom of=Task1_1.txt bs=1M count=5
dd if=/dev/urandom of=Task1_2.txt bs=1M count=5
dd if=/dev/urandom of=Task1_3.txt bs=1M count=5
#dd if=/dev/urandom of=Task1_4.txt bs=1M count=5
#dd if=/dev/urandom of=Task1_5.txt bs=1M count=5
dd if=/dev/urandom of=Task2_100.txt bs=1M count=5
dd if=/dev/urandom of=Task2_200.txt bs=1M count=5
dd if=/dev/urandom of=Task2_300.txt bs=1M count=5
dd if=/dev/urandom of=Task2_400.txt bs=1M count=5
dd if=/dev/urandom of=Task2_500.txt bs=1M count=5
dd if=/dev/urandom of=Task2_600.txt bs=1M count=5
dd if=/dev/urandom of=Task2_700.txt bs=1M count=5
dd if=/dev/urandom of=Task2_800.txt bs=1M count=5
dd if=/dev/urandom of=Task2_900.txt bs=1M count=5
dd if=/dev/urandom of=Task2_1000.txt bs=1M count=5
dd if=/dev/urandom of=Task3_01.txt bs=1M count=5
dd if=/dev/urandom of=Task3_02.txt bs=1M count=5
dd if=/dev/urandom of=Task3_03.txt bs=1M count=5
dd if=/dev/urandom of=Task3_04.txt bs=1M count=5
dd if=/dev/urandom of=Task3_05.txt bs=1M count=5
dd if=/dev/urandom of=Task3_06.txt bs=1M count=5
dd if=/dev/urandom of=Task3_07.txt bs=1M count=5
dd if=/dev/urandom of=Task3_08.txt bs=1M count=5
dd if=/dev/urandom of=Task3_09.txt bs=1M count=5
dd if=/dev/urandom of=Task3_10.txt bs=1M count=5

Server0=174.97.168.75
Server1=
Server2=
gnome-terminal -t cTask1_1 -e "bash -c \"time ./p2mpclient $Server0 61001 Task1_1.txt 500; echo cTask1_1; exec bash\""
gnome-terminal -t cTask1_2 -e "bash -c \"time ./p2mpclient $Server0 $Server1 61002 Task1_2.txt 500; echo cTask1_2; exec bash\""
gnome-terminal -t cTask1_3 -e "bash -c \"time ./p2mpclient $Server0 $Server1 $Server2 61003 Task1_3.txt 500; echo cTask1_3; exec bash\""
#gnome-terminal -t cTask1_4 -e "bash -c \"time ./p2mpclient $Server0 $Server1 $Server2 $Server3 61004 Task1_4.txt 500; echo cTask1_4; exec bash\""
#gnome-terminal -t cTask1_5 -e "bash -c \"time ./p2mpclient $Server0 $Server1 $Server2 $Server3 $Server4 61005 Task1_5.txt 500; echo cTask1_5; exec bash\""




gnome-terminal -t cTask2_100 -e "bash -c \"time ./p2mpclient $Server0 $Server1 $Server2 62001 Task2_100.txt 100; echo cTask2_100; exec bash\""
gnome-terminal -t cTask2_200 -e "bash -c \"time ./p2mpclient $Server0 $Server1 $Server2 62002 Task2_200.txt 200; echo cTask2_200; exec bash\""
gnome-terminal -t cTask2_300 -e "bash -c \"time ./p2mpclient $Server0 $Server1 $Server2 62003 Task2_300.txt 300; echo cTask2_300; exec bash\""
gnome-terminal -t cTask2_400 -e "bash -c \"time ./p2mpclient $Server0 $Server1 $Server2 62004 Task2_400.txt 400; echo cTask2_400; exec bash\""
gnome-terminal -t cTask2_500 -e "bash -c \"time ./p2mpclient $Server0 $Server1 $Server2 62005 Task2_500.txt 500; echo cTask2_500; exec bash\""
gnome-terminal -t cTask2_600 -e "bash -c \"time ./p2mpclient $Server0 $Server1 $Server2 62006 Task2_600.txt 600; echo cTask2_600; exec bash\""
gnome-terminal -t cTask2_700 -e "bash -c \"time ./p2mpclient $Server0 $Server1 $Server2 62007 Task2_700.txt 700; echo cTask2_700; exec bash\""
gnome-terminal -t cTask2_800 -e "bash -c \"time ./p2mpclient $Server0 $Server1 $Server2 62008 Task2_800.txt 800; echo cTask2_800; exec bash\""
gnome-terminal -t cTask2_900 -e "bash -c \"time ./p2mpclient $Server0 $Server1 $Server2 62009 Task2_900.txt 900; echo cTask2_900; exec bash\""
gnome-terminal -t cTask2_1000 -e "bash -c \"time ./p2mpclient $Server0 $Server1 $Server2 62010 Task2_1000.txt 1000; echo cTask2_1000; exec bash\""




gnome-terminal -t cTask3_01 -e "bash -c \"time ./p2mpclient $Server0 $Server1 $Server2 63001 Task3_01.txt 500; echo cTask3_01; exec bash\""
gnome-terminal -t cTask3_02 -e "bash -c \"time ./p2mpclient $Server0 $Server1 $Server2 63002 Task3_02.txt 500; echo cTask3_02; exec bash\""
gnome-terminal -t cTask3_03 -e "bash -c \"time ./p2mpclient $Server0 $Server1 $Server2 63003 Task3_03.txt 500; echo cTask3_03; exec bash\""
gnome-terminal -t cTask3_04 -e "bash -c \"time ./p2mpclient $Server0 $Server1 $Server2 63004 Task3_04.txt 500; echo cTask3_04; exec bash\""
gnome-terminal -t cTask3_05 -e "bash -c \"time ./p2mpclient $Server0 $Server1 $Server2 63005 Task3_05.txt 500; echo cTask3_05; exec bash\""
gnome-terminal -t cTask3_06 -e "bash -c \"time ./p2mpclient $Server0 $Server1 $Server2 63006 Task3_06.txt 500; echo cTask3_06; exec bash\""
gnome-terminal -t cTask3_07 -e "bash -c \"time ./p2mpclient $Server0 $Server1 $Server2 63007 Task3_07.txt 500; echo cTask3_07; exec bash\""
gnome-terminal -t cTask3_08 -e "bash -c \"time ./p2mpclient $Server0 $Server1 $Server2 63008 Task3_08.txt 500; echo cTask3_08; exec bash\""
gnome-terminal -t cTask3_09 -e "bash -c \"time ./p2mpclient $Server0 $Server1 $Server2 63009 Task3_09.txt 500; echo cTask3_09; exec bash\""
gnome-terminal -t cTask3_10 -e "bash -c \"time ./p2mpclient $Server0 $Server1 $Server2 63010 Task3_10.txt 500; echo cTask3_10; exec bash\""
