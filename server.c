#include"customDefinitions.h"

int main(int argc, char **argv){

	if(argc!=4){
		printf("USAGE: %s ServerListenPort# FileNameToWriteTo LossProbability \r\n",argv[0]);
		return -1;
	}
	unsigned int serverPortNumber = atoi(argv[1]);
	char *fileNameToTransfer = (char *)malloc(sizeof(char)*(NAME_MAX+1));
	strcpy(fileNameToTransfer, argv[2]);
	float lossProb = atof(argv[3]);
	unsigned int sockID = createUDPsock(serverPortNumber);
	char *buf = (char *)malloc(sizeof(char)*PROJ_MAX_SEGMENT_SIZE);
	char *replyBuf = (char *)malloc(sizeof(char)*ACK_SEG_SIZE);
	struct sockaddr_in senderConn;
	unsigned int sizeSenderConn = sizeof(struct sockaddr_in);
	FILE *fp = fopen(fileNameToTransfer,"w");
	unsigned short int checkSumValue;
	unsigned short int segType;
	unsigned int seqNo = 0;
	unsigned int tSeqNo;
	int noOfBytesRead;
	while(1){
		if((noOfBytesRead = recvfrom(sockID,buf,sizeof(char)*PROJ_MAX_SEGMENT_SIZE,0,(struct sockaddr *)&senderConn,&sizeSenderConn))<0) DieWithError("Server can't receive packets");
		//#ifdef DEBUG
		//	printf("Received a packet\r\n");
		//	fflush(stdout);
		//#endif 
		tSeqNo = (((buf[SEQ_NO_HEADER_POS] << 24) &0xFF000000)|(( buf[SEQ_NO_HEADER_POS+1] << 16) & 0x00FF0000) | ((buf[SEQ_NO_HEADER_POS+2] << 8) &0x0000FF00)|( buf[SEQ_NO_HEADER_POS+3] & 0x000000FF) );
		float tempVal = rand()/(float)RAND_MAX;
		#ifdef DEBUG
			//printf("%f Rand value", tempVal);
			//printf("No of bytes = %d",noOfBytesRead);
		#endif
		if(tempVal>lossProb){
			checkSumValue  = segmentChecksum(0,0,buf,noOfBytesRead) + 1;
			#ifdef DEBUG
				printf("checkSumValue = %d", checkSumValue);
				//fwrite(buf,sizeof(char),noOfBytesRead,stdout);
				//fflush(stdout);
			#endif
			if(!checkSumValue){//i.e., Only if checksum + 1 is equal to zero, then accept 
				if(tSeqNo == seqNo){
					segType = (((buf[SEGMENTTYPE_HEADER_POS]<<8)&0xFF00)|(buf[SEGMENTTYPE_HEADER_POS+1]&0x00FF));
					if(0x5555 == segType){
					fwrite(buf+HEADERSIZE,noOfBytesRead,sizeof(char),fp);
					makeSegment(tSeqNo,SEGMENT_TYPE_ACK,replyBuf,0);
					sendto(sockID,replyBuf,ACK_SEG_SIZE,0,(struct sockaddr *)&senderConn,sizeSenderConn);
					seqNo += noOfBytesRead;
					
					}else{
						printf("Unknown packet type\r\n");
					}
				}else{
					printf("Random Packet, Waiting for Sequence Number = %d, Received Sequence Number = %d\r\n",seqNo,tSeqNo);
					makeSegment(seqNo,SEGMENT_TYPE_ACK,replyBuf,0);//ACK last received packet.
					sendto(sockID,replyBuf,ACK_SEG_SIZE,0,(struct sockaddr *)&senderConn,sizeSenderConn);
					
				}
			}else{
				printf("Checksum fail, Sequence Number = %d\r\n",tSeqNo);
			}
		}else{
			printf("Packet Loss, Sequence Number = %d\r\n", tSeqNo);
		}
	}
	
	
	
	close(sockID);
	return 0;
}