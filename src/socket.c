//Socket.c
//#include stuff here
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
//#include <arpa/inet.h>
#include <netinet/in.h>
#include "socket.h"

static int sock;
static char buffer [1024];
static int bufPtr = 0;
static int bufSize = 1024;

struct sockaddr_in server;

int serverConnect (char *ip, int port){

    printf("%s, %d\n", ip, port);
	//Basic C socket connection stuff
	//D2L tutorial for socketConnect
	//Return 1 = conn successful, 0 = error

     
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1){
        printf("Could not create socket");
    }

    puts("Socket created\n");

    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);


    //Connect to remote server
    if (connect(sock, (struct sockaddr *)&server , sizeof(server)) < 0){
        puts("connect error");
        return 1;
    }
     
    puts("Connected");
    return 0;
	
}

int clientSend(char * msg){

	if(send(sock, msg, strlen(msg), 0) < 0){
		return 0; 
	}
	return 1;
}

int clientRecv (char *lineBuffer) {

    int i = 0;

    while (bufPtr < bufSize) { // while buffer contains data

        if (buffer[bufPtr] == '\n') {

            lineBuffer[i] = '\0'; // replace the newline with a NULL
            bufPtr++; // skip over the newline
            //printf("clientRecv at addr %p: <<%s>>\n", lineBuffer, lineBuffer);
            return i; // return a count of the # of bytes copied into lineBuffer
        }

        lineBuffer[i++] = buffer[bufPtr++];
    }

    bufSize = recv(sock, buffer, 1024, 0); // read from socket into buffer
    bufPtr = 0; // reset our read index to the beginning of buffer
    return i + clientRecv(&lineBuffer[i]); // recurse
}
