#!/bin/bash
echo "Before continuing, make sure you configure your router to forward packets arriving at port numbers 61001-61005,62001-62010,63001-63010 to your system."
echo "Once Done, Press [ENTER]"
read throw
echo "Do you like to run the server(Server[0/1/2]) or client(Client) on this system?"
read servORcli
if [[ "$servORcli" == "Server"* ]]; then
	#make -f makefileClient.mak
	make -f makefileServer.mak
	sleep 1
	rm *.o
	chmod 755 ./scriptForTask123_$servORcli.sh
	./scriptForTask123_$servORcli.sh
else
	make -f makefileClient.mak
	#make -f makefileServer.mak
	sleep 1
	rm *.o
	echo "Please configure the file(scriptForTask123_$servORcli.sh) that will open now in gedit to inform the client about server's IP address"
	echo "Press [ENTER], when done"
	
	gedit ./scriptForTask123_$servORcli.sh --new-window
	read throw	
	chmod 755 ./scriptForTask123_$servORcli.sh
	./scriptForTask123_$servORcli.sh
fi

