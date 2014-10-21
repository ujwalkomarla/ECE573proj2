#include<stdio.h>
#include<limits.h> //HOST_NAME_MAX = 255, NAME_MAX = 255
#include<stdlib.h>
#include<string.h>
#include"customFunctions.h"
#include<sys/types.h>
#include<sys/socket.h>

int main(int argc, char **argv){
	char *fileNameToTransfer = (char *)malloc(sizeof(char)* (NAME_MAX+1));
	char **serverIP; //Array of Pointers from malloc
	unsigned int segmentSize; //MSS
	unsigned int serverPortNumber; //Server Listening Port
	unsigned int numberOfServers; //Number of Servers
	unsigned int i;
	unsigned int sockID;
	FILE *fileToTransfer;
	
	if(argc<5){
		if(1==argc){
			printf(" FileNameToTransfer MSS #ServerPortNumber NumberOfServers ");
			scanf("%s %d %d %d", fileNameToTransfer, &segmentSize, &serverPortNumber, &numberOfServers);
			serverIP = malloc(sizeof(char *) * numberOfServers);
			for(i=0;i<numberOfServers;i++){
				serverIP[i] = (char *)malloc(sizeof(char)* (HOST_NAME_MAX+1));
				printf("\r\nServer-%d : ",i);
				scanf("%s",serverIP[i]);
			}
		}
		else{
			printf("USAGE: %s FileNameToTransfer MSS #ServerPortNumber ServerIP(s)\r\n",argv[0]);
			return -1;
		}
	}else{
		
		strcpy(fileNameToTransfer,argv[1]);
		segmentSize = atoi(argv[2]);
		serverPortNumber = atoi(argv[3]);
		numberOfServers = argc-4;
		serverIP = malloc(sizeof(char *) * numberOfServers);
		for(i=4;i<argc;i++){
			serverIP[i-4] = (char *)malloc(sizeof(char)* (HOST_NAME_MAX+1));
			strcpy(serverIP[i-4],argv[i]);
		}
	}
	fileToTransfer = fopen(fileNameToTransfer,"r");
	if(NULL==fileToTransfer) DieWithError("Couldn't open the file to be transferred\r\n");
	
	sockID = connectUDPsock();
	
	
	
	
	
	
	
	
	close()
	
	return 0;
}