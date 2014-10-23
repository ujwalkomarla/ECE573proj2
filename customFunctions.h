#include<stdio.h>
void DieWithError(char *);
int createUDPsock(void);
void makeSegment(unsigned int, unsigned short int, char *, unsigned int);
unsigned short int segmentChecksum(unsigned int, unsigned short int, unsigned short int *, unsigned int);
unsigned int sendSegment(unsigned int **, unsigned int, unsigned int , char *, unsigned int);