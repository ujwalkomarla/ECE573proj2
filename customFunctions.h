#include<stdio.h>
void DieWithError(char *);
int createUDPsock(void);
void makeSegment(unsigned int, unsigned short int, char *, unsigned int);
unsigned int segmentChecksum(unsigned int, unsigned short int, unsigned short int *, unsigned int);