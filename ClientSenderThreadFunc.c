#include"customDefinitions.h"



void* ClientSenderThreadFunc(void *msg){	
	struct threadArgument *rcvdArgument = (struct threadArgument *)msg;
	unsigned int segmentSize = rcvdArgument->fileTransferInfo->segmentSize;
	char *buf = (char *) malloc(segmentSize*sizeof(char));
	char *fileNameToTransfer = rcvdArgument->fileTransferInfo->fileNameToTransfer;
	FILE *fileToTransfer = fopen(fileNameToTransfer,"r");
	if(NULL==fileToTransfer) DieWithError("Couldn't open the file to be transferred\r\n");
	unsigned int seqNo = 0;
	unsigned int MaxNoOfDataBytesInSegment = segmentSize*sizeof(char) - HEADERSIZE;
	int fileReadSize;
	while((fileReadSize = fread((buf + HEADERSIZE), sizeof(char), MaxNoOfDataBytesInSegment, fileToTransfer))>0){
		
		makeSegment(seqNo, SEGMENT_TYPE_DATA, buf, fileReadSize);
		sendSegment(SEND, rcvdArgument->serverInfo,buf,(fileReadSize+HEADERSIZE));
		
		seqNo += segmentSize;
	}
	return NULL;
}	
	
	
	
	

	
	
	
	
	
	
/*
Thread Parameters: (fileNameToTransfer, segmentSize), (struct sockaddr_in ClientServerConn, serverPortNumber(Doesn't that info be in sockaddr_in), numberOfServers)
*/