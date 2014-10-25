#include<stdio.h>
#include<stdarg.h>
#include<limits.h> //HOST_NAME_MAX = 255, NAME_MAX = 255
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h> //close()
#include<arpa/inet.h>//inet_addr()
#include<netinet/in.h>
#include<pthread.h>
#include<signal.h>
#define itimerspec linux_itimerspec
#define timespec linux_timespec
//#define timeval linux_timeval
#include<sys/time.h>
//#undef timeval
#undef timespec
#undef itimerspec


#define HEADERSIZE 8 //i.e., Seq. No. is 32-bit(4 byte) Checksum 16-bit(2) Packet Type Indicator 16-bit(1)

#define SEGMENT_TYPE_DATA 1
#define SEGMENT_TYPE_ACK 0
#define SEQ_NO_HEADER_POS 0
#define CHECKSUM_HEADER_POS 4
#define SEGMENTTYPE_HEADER_POS 6

#define ACK_SEG_SIZE 8

#define ESTIMATED_RTT_S 0
#define ESTIMATED_RTT_uS 5000

#define SEND 3
#define RESEND 0
struct tFileTransferInfo{
	char *fileNameToTransfer;
	unsigned int segmentSize;
	unsigned int seqNo;
};
struct tServerInfo{
	struct sockaddr_in **ClientServerSockAddrInfo;
	unsigned int sockID;
	unsigned int numberOfServers;
	unsigned int *serverACK;
};
struct threadArgument{
	struct tFileTransferInfo *fileTransferInfo;
	struct tServerInfo *serverInfo;
};
	
	
void* ClientSenderThreadFunc(void *);	
void* ClientReceiverThreadFunc(void *);
void DieWithError(char *);
int createUDPsock(unsigned int);
void makeSegment(unsigned int, unsigned short int, char *, unsigned int);
unsigned short int segmentChecksum(unsigned int, unsigned short int, unsigned short int *, unsigned int);
//unsigned int sendSegment(unsigned int **, unsigned int, unsigned int ,unsigned int, char *, unsigned int);
//unsigned int sendSegment(struct tServerInfo *,char *,unsigned int);
unsigned int sendSegment(unsigned int, ...);
void timeOut(int);