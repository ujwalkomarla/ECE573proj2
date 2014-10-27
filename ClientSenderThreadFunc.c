#include"customDefinitions.h"



void* ClientSenderThreadFunc(void *msg){	
	extern unsigned int SEND_NEXT;
	unsigned int i;
	struct threadArgument *rcvdArgument = (struct threadArgument *)msg;
	unsigned int segmentSize = rcvdArgument->fileTransferInfo->segmentSize;
	unsigned int tSeqNo;
	char *buf = (char *) malloc(segmentSize*sizeof(char));
	char *fileNameToTransfer = rcvdArgument->fileTransferInfo->fileNameToTransfer;
	FILE *fileToTransfer = fopen(fileNameToTransfer,"r");
	if(NULL==fileToTransfer) DieWithError("Couldn't open the file to be transferred\r\n");
	unsigned int MaxNoOfDataBytesInSegment = segmentSize*sizeof(char) - HEADERSIZE;
	int fileReadSize;
	unsigned int DONE=0;
	while(!DONE){
		while(!SEND_NEXT);
		if(0==(fileReadSize = fread((buf + HEADERSIZE), sizeof(char), MaxNoOfDataBytesInSegment, fileToTransfer))) DONE=1;
		#ifdef DEBUG
		printf("Sending a packet with sequence number %d FileReadSize %d",rcvdArgument->fileTransferInfo->seqNo, fileReadSize);
		fflush(stdout);
		#endif
		//This instruction is required first, so that the older ACK's are not accepted
		tSeqNo = rcvdArgument->fileTransferInfo->seqNo;
		(rcvdArgument->fileTransferInfo->seqNo) += segmentSize;
		for(i = 0;i<rcvdArgument->serverInfo->numberOfServers;i++){
			rcvdArgument->serverInfo->serverACK[i] = 0;
		}
		makeSegment(tSeqNo, SEGMENT_TYPE_DATA, buf, fileReadSize);
		#ifdef DEBUG
			//fwrite(buf,sizeof(char),segmentSize,stdout);
			//fflush(stdout);
		#endif
		SEND_NEXT = 0;
		sendSegment(SEND, rcvdArgument->serverInfo,buf,(fileReadSize+HEADERSIZE));
		
	}
	while(!SEND_NEXT);//For the last packet
	return NULL;
}	
	
	
	
	

	
	
	
	
	
	
/*
Thread Parameters: (fileNameToTransfer, segmentSize), (struct sockaddr_in ClientServerConn, serverPortNumber(Doesn't that info be in sockaddr_in), numberOfServers)
*/