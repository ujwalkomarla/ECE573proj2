//#includes
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<limits.h>  //NAME_MAX
#include<unistd.h>
#include<errno.h>

//#defines
#define PROJ_MAX_SEGMENT_SIZE 549;
#define SERVERLISTENPORT 65423;


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
	
	//Local Variables
	struct sockaddr_in serverListenSocket, clientListenSocket; 
	
	int serverListenSockId, connectedCliServSockId;	
	
	unsigned int clntLen = sizeof(clientListenSocket),recvLen;

	//Create socket
	serverListenSockId = socket(PF_INET, SOCK_DGRAM, 0);
	if(serverListenSockId == -1) DieWithError("Error Creating serverListenSockId");
        //SO_REUSEADDR -> So that we can use a socket that is in a wait state
	
	//Settings for server listen socket
	serverListenSocket.sin_family = AF_INET;
	serverListenSocket.sin_port = htons(SERVERLISTENPORT);
	serverListenSocket.sin_addr.s_addr = htonl(INADDR_ANY);
	
	//Bind
	if (bind(serverListenSockId, (struct sockaddr *) &serverListenSocket, sizeof(serverListenSocket)) == -1) DieWithError("Bind() Error");

	FILE *fp = fopen(fileNameToTransfer, "w+");
	//receive data
	while(TRUE){
		printf("Waiting for data..\n");
		fflush(stdout);
		
		if((recvLen = recvfrom(serverListenSockId,buf,sizeof(buf),0,(struct sockaddr *)&clientListenSocket,&clntLen))<0) DieWithError("Server can't receive packets");
		buf[PROJ_MAX_SEGMENT_SIZE]='\0';
		
		//write to file
		if(fp){
			if(fwrite(buf,1, recvLen,fp)!= recvLen)
			{
				fprintf(stderr, "Error writing the file: %s\n", strerror(errno));
				exit(1);
			}
			fclose(fp);
			printf("File receive..\n");
			}
		else{
			fprintf(stderr,"Error opening file: %s\n", stderr(errno));
			}
		
		}
		
		
		if((rand()/RAND_MAC)>lossProb){  	
		if(){

			}
		}
	
	


close(serverListenSockId);
return 0;
}


