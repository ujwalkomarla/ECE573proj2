#include"customDefinitions.h"



void* ClientSenderThreadFunc(void *msg){	
	extern unsigned int SEND_NEXT;
	unsigned int i;
	struct threadArgument *rcvdArgument = (struct threadArgument *)msg;
	unsigned int segmentSize = rcvdArgument->fileTransferInfo->segmentSize;
	char *buf = (char *) malloc(segmentSize*sizeof(char));
	char *fileNameToTransfer = rcvdArgument->fileTransferInfo->fileNameToTransfer;
	FILE *fileToTransfer = fopen(fileNameToTransfer,"r");
	if(NULL==fileToTransfer) DieWithError("Couldn't open the file to be transferred\r\n");
	unsigned int MaxNoOfDataBytesInSegment = segmentSize*sizeof(char) - HEADERSIZE;
	int fileReadSize;
	while((fileReadSize = fread((buf + HEADERSIZE), sizeof(char), MaxNoOfDataBytesInSegment, fileToTransfer))>0){
		while(!SEND_NEXT);
		#ifdef DEBUG
		printf("Sending a packet with sequence number %d",rcvdArgument->fileTransferInfo->seqNo);
		#endif
		//This instruction is required first, so that the older ACK's are not accepted
		(rcvdArgument->fileTransferInfo->seqNo) += segmentSize;
		for(i = 0;i<rcvdArgument->serverInfo->numberOfServers;i++){
			rcvdArgument->serverInfo->serverACK[i] = 0;
		}
		makeSegment(rcvdArgument->fileTransferInfo->seqNo, SEGMENT_TYPE_DATA, buf, fileReadSize);
		SEND_NEXT = 0;
		sendSegment(SEND, rcvdArgument->serverInfo,buf,(fileReadSize+HEADERSIZE));
		
	}
	return NULL;
}	
	
	
	
	

	
	
	
	
	
	
/*
Thread Parameters: (fileNameToTransfer, segmentSize), (struct sockaddr_in ClientServerConn, serverPortNumber(Doesn't that info be in sockaddr_in), numberOfServers)
*/