
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
	struct sockaddr_in = 
	while(1){
		if(recvfrom(sockID,buf,sizeof(buf),0,(struct sockaddr *)&serverUDP,&serverUDPlen)<0) DieWithError("Server can't receive packets");
		if((rand()/RAND_MAC)>lossProb){
			if(){
			
			}
		}
	}
	
	
	
	close(sockID);
	return 0;
}