#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
//#include <arpa/inet.h> //inet_addr

int serverConnect (char *ip, int port);
int clientSend(char *msg);
int clientRecv (char *lineBuffer);