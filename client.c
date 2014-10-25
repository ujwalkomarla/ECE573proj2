#include"customDefinitions.h"
unsigned int SEND_NEXT = 1;
int main(int argc, char **argv){
	struct threadArgument *clientSenderThreadArgument = malloc(sizeof(struct threadArgument));
	
	
	//Variable to struct member
	//char *fileNameToTransfer = (char *)malloc(sizeof(char)* (NAME_MAX+1));
	//unsigned int segmentSize; //MSS : Scanf/Argv[?]
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
				clientSenderThreadArgument->serverInfo->ClientServerSockAddrInfo[i]->sin_port = tServerPortNumber;
				clientSenderThreadArgument->serverInfo->ClientServerSockAddrInfo[i]->sin_addr.s_addr = inet_addr(tempStr);
			}
		}
		else{
			printf("USAGE: %s FileNameToTransfer MSS #ServerPortNumber ServerIP(s)\r\n",argv[0]);
			return -1;
		}
	}else{
		
		strcpy(clientSenderThreadArgument->fileTransferInfo->fileNameToTransfer,argv[1]);
		clientSenderThreadArgument->fileTransferInfo->segmentSize = atoi(argv[2]);
		clientSenderThreadArgument->serverInfo->numberOfServers = argc-4;
		clientSenderThreadArgument->serverInfo->ClientServerSockAddrInfo = \
				malloc(sizeof(struct sockaddr_in *) * clientSenderThreadArgument->serverInfo->numberOfServers);
		clientSenderThreadArgument->serverInfo->serverACK = \
				malloc(sizeof(unsigned int) * clientSenderThreadArgument->serverInfo->numberOfServers);		
				
		for(i=4;i<argc;i++){
			clientSenderThreadArgument->serverInfo->ClientServerSockAddrInfo[i-4] = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
			clientSenderThreadArgument->serverInfo->ClientServerSockAddrInfo[i-4]->sin_family = AF_INET;
			clientSenderThreadArgument->serverInfo->ClientServerSockAddrInfo[i-4]->sin_port = atoi(argv[3]);
			clientSenderThreadArgument->serverInfo->ClientServerSockAddrInfo[i-4]->sin_addr.s_addr = inet_addr(argv[i]);
		}
	}
	//By sending 0 we are letting the OS to choose a port for us.
	clientSenderThreadArgument->serverInfo->sockID = createUDPsock(0);
	
	
    if(0 != pthread_create( &clientSenderThread, NULL, ClientSenderThreadFunc, clientSenderThreadArgument)) DieWithError("Error - pthread_create()");	
	// What parameters are required to be sent?
    if(0 !=pthread_create( &clientReceiverThread, NULL, ClientReceiverThreadFunc, clientSenderThreadArgument)) DieWithError("Error - pthread_create()");
	pthread_join( clientSenderThread, NULL);
	pthread_join( clientReceiverThread, NULL);
	close(clientSenderThreadArgument->serverInfo->sockID);
	return 0;
}
