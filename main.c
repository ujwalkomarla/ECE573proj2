#include<stdio.h>
#include<limits.h> //HOST_NAME_MAX = 255, NAME_MAX = 255
int main(int argc, char **argv){
	char *fileNameToTransfer = (char *)malloc(sizeof(char)* (NAME_MAX+1));
	char *serverIP;
	unsigned int segmentSize; //MSS
	unsigned int serverPortNumber; //Server Listening Port
	unsigned int numberOfServers; //Number of Servers
	
	if(argc<5){
		if(1==argc){
			printf(" FileNameToTransfer MSS #ServerPortNumber NumberOfServers ");
			scanf("%s %d %d %d", fileNameToTransfer, &segmentSize, &serverPortNumber, &numberOfServers);
			serverIP = (char *)malloc(sizeof(char)* (HOST_NAME_MAX+1) * numberOfServers);
			for(i=0;i<numberOfServers;i++){
				printf("\r\nServer-%d : ",i);
				scanf("%d",serverIP[i]);
			}
		}
		else{
			printf("USAGE: %s FileNameToTransfer MSS #ServerPortNumber ServerIPs\r\n",argv[0]);
			return -1;
		}
	}
	
	strcpy(fileNameToTransfer,argv[1]);
	segmentSize = argv[2];
	serverPortNumber = argv[3];
	for(i=4;i<argc;i++){
		serverIP[i-4] = argv[i];
	}
	
}