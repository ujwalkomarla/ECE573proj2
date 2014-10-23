#include"customDefinitions.h"

void timeOut(int sig){

}
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
	unsigned short int checkSumVal;
	buf[SEQ_NO_HEADER_POS] = (seqNo>>24) & 0xFF;
	buf[SEQ_NO_HEADER_POS+1] = (seqNo>>16) & 0xFF;
	buf[SEQ_NO_HEADER_POS+2] = (seqNo>>8) & 0xFF;
	buf[SEQ_NO_HEADER_POS+3] = seqNo & 0xFF;
	
	if(1 == segmentType) segmentType =0x5555;
	else if(0 == segmentType) segmentType =0xAAAA;
		 else DieWithError("Don't know the packet type");
		 
	buf[SEGMENTTYPE_HEADER_POS] = (segmentType>>8) & 0xFF;
	buf[SEGMENTTYPE_HEADER_POS+1] = segmentType & 0xFF;
	if(0 != dataLength)
		//Disregard warning of char * to unsigned short in *
		checkSumVal = segmentChecksum(seqNo, segmentType, buf + HEADERSIZE, dataLength);
	
	buf[CHECKSUM_HEADER_POS] = (checkSumVal>>8) & 0xFF;
	buf[CHECKSUM_HEADER_POS+1] = checkSumVal & 0xFF; 

	return;
}





unsigned short int segmentChecksum(unsigned int seqNo, unsigned short int segmentType, unsigned short int *buf, unsigned int dataLength){
	unsigned int sum=0;
	unsigned int i;
	if(1==dataLength%2) {dataLength++; buf[dataLength] = 0;}//Padding
	sum += ((seqNo>>16)&0xFFFF) + (seqNo&0XFFFF);
	sum += segmentType;
	for(i=0;i<dataLength/2;i++){//Accessed as short int, so dataLength needs to be divided by two
		sum += buf[i];
	}
	while(sum>>16){
		sum = ((sum>>16)&0xFFFF) + (sum&0xFFFF);
	}
	return ((unsigned short int)~sum); //1's complement	
}

unsigned int sendSegment(struct tServerInfo *serversInfo, char *buf, unsigned int segmentSize){
	int i;
	struct itimerval new;
	for(i=0; i<(serversInfo->numberOfServers); i++){
	sendto(serversInfo->sockID,buf,segmentSize,0,(struct sockaddr *)serversInfo->ClientServerSockAddrInfo[i],sizeof(struct sockaddr_in));
	}
	new.it_interval.tv_sec = 0;
	new.it_interval.tv_usec = 0;
	new.it_value.tv_sec = 0;
	new.it_value.tv_usec = ESTIMATED_RTT_uS;
	if (setitimer (ITIMER_REAL, &new, NULL) < 0) DieWithError("Couldn't create the timer");
	signal (SIGALRM, timeOut);
	return 0;
}