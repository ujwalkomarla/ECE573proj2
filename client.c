#include"customDefinitions.h"
unsigned int SEND_NEXT = 1;
pthread_mutex_t sendNextMutex;
pthread_cond_t sendNextWaitOn1;
int main(int argc, char **argv){
	struct threadArgument *clientSenderThreadArgument = malloc(sizeof(struct threadArgument));
	pthread_mutex_init(&sendNextMutex,NULL);
	pthread_cond_init(&sendNextWaitOn1,NULL);
	
	//Variable to struct member
	//char *fileNameToTransfer = (char *)malloc(sizeof(char)* (NAME_MAX+1));
	//unsigned int segmentSize; //MSS : Scanf/Argv[?]
	clientSenderThreadArgument->fileTransferInfo = malloc(sizeof(struct tFileTransferInfo));
	clientSenderThreadArgument->serverInfo = malloc(sizeof(struct tServerInfo));
	
	clientSenderThreadArgument->fileTransferInfo->fileNameToTransfer = (char *)malloc(sizeof(char)* (NAME_MAX+1));
	
	
	//This information can directly be saved in a sockaddr_in struct variable info.(IP address and Server Listening Port)
	//unsigned int **serverIP; //Array of Pointers from malloc
	//unsigned int serverPortNumber; //Server Listening Port
	//unsigned int numberOfServers; //Number of Servers
	
	
	char *tempStr = (char *)malloc(sizeof(char *));

	pthread_t clientSenderThread;
	pthread_t clientReceiverThread;
	unsigned int i;	
	
	if(argc<5){
		if(1==argc){
			unsigned int tServerPortNumber;
			printf(" FileNameToTransfer MSS #ServerPortNumber NumberOfServers ");
			scanf("%s %d %d %d", clientSenderThreadArgument->fileTransferInfo->fileNameToTransfer, \
							&(clientSenderThreadArgument->fileTransferInfo->segmentSize), \
							&tServerPortNumber, \
							&(clientSenderThreadArgument->serverInfo->numberOfServers));
			clientSenderThreadArgument->serverInfo->ClientServerSockAddrInfo = \
				malloc(sizeof(struct sockaddr_in *) * clientSenderThreadArgument->serverInfo->numberOfServers);
			clientSenderThreadArgument->serverInfo->serverACK = \
				malloc(sizeof(unsigned int) * clientSenderThreadArgument->serverInfo->numberOfServers);	
			for(i=0;i<(clientSenderThreadArgument->serverInfo->numberOfServers);i++){
				printf("\r\nServer-%d : ",i);
				scanf("%s",tempStr);
				
				clientSenderThreadArgument->serverInfo->ClientServerSockAddrInfo[i] = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
				clientSenderThreadArgument->serverInfo->ClientServerSockAddrInfo[i]->sin_family = AF_INET;
				clientSenderThreadArgument->serverInfo->ClientServerSockAddrInfo[i]->sin_port = htons(tServerPortNumber);
				clientSenderThreadArgument->serverInfo->ClientServerSockAddrInfo[i]->sin_addr.s_addr = inet_addr(tempStr);
			}
		}
		else{
			printf("USAGE: %s ServerIP(s) #ServerPortNumber FileNameToTransfer MSS \r\n",argv[0]);
			return -1;
		}
	}else{
				
		strcpy(clientSenderThreadArgument->fileTransferInfo->fileNameToTransfer,argv[argc-2]);
		clientSenderThreadArgument->fileTransferInfo->segmentSize = atoi(argv[argc-1]);
		clientSenderThreadArgument->serverInfo->numberOfServers = argc-4;
		clientSenderThreadArgument->serverInfo->ClientServerSockAddrInfo = \
				malloc(sizeof(struct sockaddr_in *) * clientSenderThreadArgument->serverInfo->numberOfServers);
		clientSenderThreadArgument->serverInfo->serverACK = \
				malloc(sizeof(unsigned int) * clientSenderThreadArgument->serverInfo->numberOfServers);		
				
		for(i=1;i<argc-3;i++){
			clientSenderThreadArgument->serverInfo->ClientServerSockAddrInfo[i-1] = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
			clientSenderThreadArgument->serverInfo->ClientServerSockAddrInfo[i-1]->sin_family = AF_INET;
			clientSenderThreadArgument->serverInfo->ClientServerSockAddrInfo[i-1]->sin_port = htons(atoi(argv[argc-3]));
			clientSenderThreadArgument->serverInfo->ClientServerSockAddrInfo[i-1]->sin_addr.s_addr = inet_addr(argv[i]);
		
		}
	}
	//By sending 0 we are letting the OS to choose a port for us.
	clientSenderThreadArgument->serverInfo->sockID = createUDPsock(0);
	
    if(0 != pthread_create( &clientSenderThread, NULL, ClientSenderThreadFunc, clientSenderThreadArgument)) DieWithError("Error - pthread_create()");	
	// What parameters are required to be sent?
    if(0 !=pthread_create( &clientReceiverThread, NULL, ClientReceiverThreadFunc, clientSenderThreadArgument)) DieWithError("Error - pthread_create()");
	pthread_join( clientSenderThread, NULL);
	//printf("clientSenderThreadTerminate");
	//pthread_join( clientReceiverThread, NULL);
	pthread_cancel(clientReceiverThread);
	pthread_mutex_destroy(&sendNextMutex);
	pthread_cond_destroy(&sendNextWaitOn1);
	close(clientSenderThreadArgument->serverInfo->sockID);
	return 0;
}
