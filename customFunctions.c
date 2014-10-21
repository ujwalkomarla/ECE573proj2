#include<stdio.h>
#include"customFunctions.h"
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
void DieWithError(char *msg){
	perror(msg);
	exit(EXIT_FAILURE);
}
int createUDPsock(void){
	int sockID;
	if ((sockID = socket(AF_INET, SOCK_DGRAM, 0)) < 0) DieWithError("Unable to create a socket");
	struct sockaddr_in myAddr;
	memset((char *)&myAddr, 0 , sizeof(myAddr));
	myAddr.sin_family = AF_INET;
	myAddr.sin_addr.s.addr = htonl(INADDR_ANY);
	myAddr.sin_port = htons(0);//Let the OS chose a port on behalf of us.
	if(bind(sockID,(struct sockaddr *)&myAddr, sizeof(myAddr))<0) DieWithError("Unable to do a bind on socket"); 
	return sockID;
}