#include<stdio.h>
#include<limits.h> //HOST_NAME_MAX = 255, NAME_MAX = 255
#include<stdlib.h>
#include<string.h>
#include"customFunctions.h"
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h> //close()
#include<arpa/inet.h>//inet_addr()
#define HEADERSIZE 8 //i.e., Seq. No. is 32-bit(4 byte) Checksum 16-bit(2) Packet Type Indicator 16-bit(1)

#define SEGMENT_TYPE_DATA 1
#define SEGMENT_TYPE_ACK 0
int main(int argc, char **argv){
	char *fileNameToTransfer = (char *)malloc(sizeof(char)* (NAME_MAX+1));
	char *tempStr = (char *)malloc(sizeof(char *));
	unsigned int **serverIP; //Array of Pointers from malloc
	unsigned int segmentSize; //MSS
	unsigned int serverPortNumber; //Server Listening Port
	unsigned int numberOfServers; //Number of Servers
	unsigned int i;
	unsigned int sockID;
	char *buf;
	unsigned int seqNo;
	
	unsigned int MaxNoOfDataBytesInSegment;
	int fileReadSize;
	FILE *fileToTransfer;
	
	if(argc<5){
		if(1==argc){
			printf(" FileNameToTransfer MSS #ServerPortNumber NumberOfServers ");
			scanf("%s %d %d %d", fileNameToTransfer, &segmentSize, &serverPortNumber, &numberOfServers);
			serverIP = malloc(sizeof(unsigned int *) * numberOfServers);
			for(i=0;i<numberOfServers;i++){
				serverIP[i] = (unsigned int *)malloc(sizeof(unsigned int));
				printf("\r\nServer-%d : ",i);
				scanf("%s",tempStr);
				*serverIP[i] = inet_addr(tempStr);
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
		serverIP = malloc(sizeof(unsigned int *) * numberOfServers);
		for(i=4;i<argc;i++){
			serverIP[i-4] = (unsigned int *)malloc(sizeof(unsigned int));
			*serverIP[i-4] = inet_addr(argv[i]);
		}
	}
	sockID = createUDPsock();
	buf = (char *) malloc(segmentSize*sizeof(char));
	fileToTransfer = fopen(fileNameToTransfer,"r");
	if(NULL==fileToTransfer) DieWithError("Couldn't open the file to be transferred\r\n");
	seqNo = 0;
	MaxNoOfDataBytesInSegment = segmentSize*sizeof(char) - HEADERSIZE;
	while((fileReadSize = fread((buf + HEADERSIZE), sizeof(char), MaxNoOfDataBytesInSegment, fileToTransfer))>0){
		
		makeSegment(seqNo, SEGMENT_TYPE_DATA, buf, fileReadSize);
		sendSegment(serverIP,serverPortNumber,numberOfServers,buf,segmentSize);
		
		seqNo += segmentSize;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	close(sockID);
	
	return 0;
}
