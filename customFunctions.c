#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include"customFunctions.h"
#define HEADERSIZE 8 //i.e., Seq. No. is 32-bit(4 byte) Checksum 16-bit(2) Packet Type Indicator 16-bit(1)
#define SEQ_NO_HEADER_POS 0
#define CHECKSUM_HEADER_POS 4
#define SEGMENTTYPE_HEADER_POS 6

void DieWithError(char *msg){
	perror(msg);
	exit(EXIT_FAILURE);
}
int createUDPsock(void){
	int sockID;
	if ((sockID = socket(AF_INET, SOCK_DGRAM, 0)) < 0) DieWithError("Unable to create a socket");
	struct sockaddr_in myAddr;
	memset((struct sockaddr_in *)&myAddr, 0 , sizeof(myAddr));
	myAddr.sin_family = AF_INET;
	myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myAddr.sin_port = htons(0);//Let the OS chose a port on behalf of us.
	if(bind(sockID,(struct sockaddr *)&myAddr, sizeof(myAddr))<0) DieWithError("Unable to do a bind on socket"); 
	return sockID;
}



void makeSegment(unsigned int seqNo, unsigned short int segmentType, char *buf, unsigned int dataLength){

	buf[SEQ_NO_HEADER_POS] = (seqNo>>24) & 0xFF;
	buf[SEQ_NO_HEADER_POS+1] = (seqNo>>16) & 0xFF;
	buf[SEQ_NO_HEADER_POS+2] = (seqNo>>8) & 0xFF;
	buf[SEQ_NO_HEADER_POS+3] = seqNo & 0xFF;
	
	if(segmentType = 1) packetType =0x5555;
	else if(segmentType = 0) packetType =0xAAAA;
		 else DieWithError("Don't know the packet type");
		 
	buf[SEGMENTTYPE_HEADER_POS] = (packetType>>8) & 0xFF;
	buf[SEGMENTTYPE_HEADER_POS+1] = packetType & 0xFF;
	if(0 != dataLength)
		//Disregard warning of char * to unsigned short in *
		checkSumVal = segmentChecksum(seqNo, packetType, buf + HEADERSIZE, dataLength);
	
	buf[CHECKSUM_HEADER_POS] = (checkSumVal>>8) & 0xFF;
	buf[CHECKSUM_HEADER_POS+1] = checkSumVal & 0xFF; 

	return;
}





unsigned short int segmentChecksum(unsigned int seqNo, unsigned short int packetType, unsigned short int *buf, unsigned int dataLength){
unsigned int sum=0;

if(1==dataLength%2) {dataLength++; buf[dataLength] = 0;}//Padding
sum + = (seqNo>>16)&0xFFFF + (seqNo&0XFFFF);
sum + = packetType;
for(i=0;i<dataLength/2;i++){//Accessed as short int, so dataLength needs to be divided by two
	sum + = buf[i];
}
while(sum>>16)
	sum = (sum>>16)&0xFFFF + (sum&0xFFFF);

return ((unsigned short int)~sum); //1's complement	
}