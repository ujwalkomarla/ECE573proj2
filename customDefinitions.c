#include"customDefinitions.h"

void timeOut(int sig){
	signal(sig, SIG_IGN);
	sendSegment(RESEND);
	#ifdef DEBUG
		//printf("Time out");
		//fflush(stdout);
	#endif
	
}
void DieWithError(char *msg){
	perror(msg);
	exit(EXIT_FAILURE);
}
int createUDPsock(unsigned int tSocket){
//if Input parameter is Zero, we let the OS to choose a port on behalf of us
	int sockID;
	if ((sockID = socket(AF_INET, SOCK_DGRAM, 0)) < 0) DieWithError("Unable to create a socket");
	struct sockaddr_in myAddr;
	memset((struct sockaddr_in *)&myAddr, 0 , sizeof(myAddr));
	myAddr.sin_family = AF_INET;
	myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myAddr.sin_port = htons(tSocket);
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
	#ifdef DEBUG
		//printf("CheckSumVal = %d",checkSumVal);
	#endif
		checkSumVal = ~checkSumVal;
	#ifdef DEBUG
		//printf("CheckSumVal = %d",checkSumVal);
	#endif
	buf[CHECKSUM_HEADER_POS] =  (checkSumVal>>8) & 0xFF;
	buf[CHECKSUM_HEADER_POS+1] = checkSumVal & 0xFF; 
	
	#ifdef DEBUG
		//unsigned short int throw = segmentChecksum(0, 0, buf, dataLength+HEADERSIZE) + 1;
		//printf("Throw = %d",throw);
		//fflush(stdout);
	#endif
	
	return;
}





unsigned short int segmentChecksum(unsigned int seqNo, unsigned short int segmentType, char *buf, unsigned int dataLength){
	unsigned int sum=0;
	unsigned int i;
	if(1==dataLength%2) {dataLength++; buf[dataLength] = 0;}//Padding
	sum += ((seqNo>>16)&0xFFFF) + (seqNo&0XFFFF);
	sum += segmentType;
	for(i=0;i<(dataLength);i+=2){
		
		sum += ((buf[i]<<8)&0xFF00) + (buf[i+1]&0x00FF);
	}
	while(sum>>16){
		sum = (sum>>16) + (sum&0xFFFF);
	}
	return ((unsigned short int)sum); //1's complement	
}
//RESEND = 0
//SEND = 3
//unsigned int sendSegment(struct tServerInfo *serversInfo, char *buf, unsigned int segmentSize){
unsigned int sendSegment(unsigned int reSendOrSend, ...){
	
	
	static char *tBuf;
	static unsigned int segmentSize;
	static struct tServerInfo *serversInfo;
	
	if(reSendOrSend){
	va_list arguments;
	va_start(arguments, reSendOrSend);
	serversInfo = va_arg ( arguments, struct tServerInfo * );
	tBuf = va_arg ( arguments, char * ); 
	segmentSize = va_arg ( arguments, unsigned int );
	va_end(arguments);
	#ifdef DEBUG
	//printf("Segment Size %d Buffer = ",segmentSize);
	//fwrite(tBuf,sizeof(char),segmentSize,stdout);
	//fflush(stdout);
	#endif
	}else{
	unsigned int tSeqNo = (((tBuf[SEQ_NO_HEADER_POS] << 24) &0xFF000000)|(( tBuf[SEQ_NO_HEADER_POS+1] << 16) & 0x00FF0000) | ((tBuf[SEQ_NO_HEADER_POS+2] << 8) &0x0000FF00)|( tBuf[SEQ_NO_HEADER_POS+3] & 0x000000FF) );
	printf("Timeout, Sequence number = %d\r\n",tSeqNo);
	}
		
	int i;
	struct itimerval new;
	for(i=0; i<serversInfo->numberOfServers; i++){
	sendto(serversInfo->sockID,tBuf,segmentSize,0,(struct sockaddr *)serversInfo->ClientServerSockAddrInfo[i],sizeof(struct sockaddr_in));
	}
	new.it_interval.tv_sec = 0;
	new.it_interval.tv_usec = 0;
	new.it_value.tv_sec = ESTIMATED_RTT_S;
	new.it_value.tv_usec = ESTIMATED_RTT_uS;
	if (setitimer (ITIMER_REAL, &new, NULL) < 0) DieWithError("Couldn't create the timer");
	signal (SIGALRM, timeOut);
	return 0;
}