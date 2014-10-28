#include"customDefinitions.h"



void* ClientSenderThreadFunc(void *msg){	
	extern unsigned int SEND_NEXT;
	extern pthread_mutex_t sendNextMutex;
	extern pthread_cond_t sendNextWaitOn1;
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
	while(DONE==0){// !DONE
		pthread_mutex_lock(&sendNextMutex);
		while(!SEND_NEXT){
		pthread_cond_wait(&sendNextWaitOn1,&sendNextMutex);
		}
		fileReadSize = fread((buf + HEADERSIZE), sizeof(char), MaxNoOfDataBytesInSegment, fileToTransfer);
		if(feof(fileToTransfer)){
		
		//printf(" %ld ",ftell(fileToTransfer));printf("EOF");fflush(stdout);
		fileReadSize=ftell(fileToTransfer)%MaxNoOfDataBytesInSegment;
		DONE = 1;
		}
		
		
		#ifdef DEBUG
		//printf("File Read Size = %d",fileReadSize);
		//printf("Sending a packet with sequence number %d FileReadSize %d",rcvdArgument->fileTransferInfo->seqNo, fileReadSize);
		//fflush(stdout);
		#endif
		//This instruction is required first, so that the older ACK's are not accepted
		tSeqNo = rcvdArgument->fileTransferInfo->seqNo;
		(rcvdArgument->fileTransferInfo->seqNo) += fileReadSize+HEADERSIZE;
		for(i = 0;i<rcvdArgument->serverInfo->numberOfServers;i++){
			rcvdArgument->serverInfo->serverACK[i] = 0;
		}
		makeSegment(tSeqNo, SEGMENT_TYPE_DATA, buf, fileReadSize);
		#ifdef DEBUG
			//fwrite(buf,sizeof(char),segmentSize,stdout);
			//fflush(stdout);
		#endif
		SEND_NEXT = 0;
		pthread_mutex_unlock(&sendNextMutex);
		sendSegment(SEND, rcvdArgument->serverInfo,buf,(fileReadSize+HEADERSIZE));
		
	}
	//printf("Exit loop, %d",tSeqNo);
	
	while(!SEND_NEXT);//For the last packet
	signal(SIGALRM, SIG_IGN);
	return NULL;
}	
/*
Thread Parameters: (fileNameToTransfer, segmentSize), (struct sockaddr_in ClientServerConn, serverPortNumber(Doesn't that info be in sockaddr_in), numberOfServers)
*/