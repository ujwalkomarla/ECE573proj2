#include"customDefinitions.h"


void *ClientReceiverThreadFunc(void *msg){
	extern unsigned int SEND_NEXT;
	struct threadArgument *rcvdArgument = (struct threadArgument *)msg;
	char *buf = (char *) malloc(ACK_SEG_SIZE*sizeof(char));
	struct sockaddr_in clientRcvrUDP;
	unsigned int clientRcvrUDPlen = sizeof(struct sockaddr_in); 
	unsigned int seqNo;
	unsigned short int segType;
	unsigned int i;
	unsigned int countOfACKs;
	int noOfBytesRead;
	while(1){
		if((noOfBytesRead = recvfrom(rcvdArgument->serverInfo->sockID,buf,ACK_SEG_SIZE*sizeof(char),0,(struct sockaddr *)&clientRcvrUDP,&clientRcvrUDPlen))<0) DieWithError("Client Receiver can't receive packets");
		#ifdef DEBUG
		printf("Received an ACK probably?");
		#endif
		//unsigned short int checkSumValue  = segmentChecksum(0,0,buf,ACK_SEG_SIZE) + 1;
		//if(!checkSumValue){//i.e., Only if checksum + 1 is equal to zero, then accept 
			if(ACK_SEG_SIZE == noOfBytesRead){
				seqNo = (((buf[SEQ_NO_HEADER_POS] << 24) &0xFF000000)|(( buf[SEQ_NO_HEADER_POS+1] << 16) & 0x00FF0000) | ((buf[SEQ_NO_HEADER_POS+2] << 8) &0x0000FF00)|( buf[SEQ_NO_HEADER_POS+3] & 0x000000FF) );
				if(seqNo == rcvdArgument->fileTransferInfo->seqNo){
					segType = (((buf[SEGMENTTYPE_HEADER_POS]<<8)&0xFF00)|(buf[SEGMENTTYPE_HEADER_POS+1]&0x00FF));
					if(0xAAAA == segType){
						countOfACKs = 0;
						for(i=0;i<rcvdArgument->serverInfo->numberOfServers;i++){
							if(clientRcvrUDP.sin_addr.s_addr==rcvdArgument->serverInfo->ClientServerSockAddrInfo[i]->sin_addr.s_addr)	
								rcvdArgument->serverInfo->serverACK[i] = 1;
							//ORDER of these IFs are important. Don't mess
							if(1==rcvdArgument->serverInfo->serverACK[i])
								countOfACKs++;	
						}
						if(countOfACKs == rcvdArgument->serverInfo->numberOfServers){
							SEND_NEXT = 1;
						}
					}else{
						printf("Unknown packet type\r\n");
					}
				}else{
					printf("ACK for older packet, Waiting for %d, Received %d",rcvdArgument->fileTransferInfo->seqNo,seqNo);
				}
			}	
		/*}*/
	}
return NULL;
}