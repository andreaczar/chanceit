//Socket.c
//#include stuff here
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "socket.h"

static int socket_desc;
static char buffer [1024];
static int bufPtr = 0;
static int bufSize = 0;



int serverConnect (char *IP, int port){

	//Basic C socket connection stuff
	//D2L tutorial for socketConnect
	//Return 1 = conn successful, 0 = error
	struct sockaddr_in server;
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1){
        printf("Could not create socket");
    }

    puts("Socket created\n");

    server.sin_addr.s_addr = inet_addr(&IP);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
 
    //Connect to remote server
    if (connect(socket_desc, (struct sockaddr *)&server , sizeof(server)) < 0){
        puts("connect error");
        return 1;
    }
     
    puts("Connected");
    return 0;
	
}

int server_send(char * msg){

	if(send(socket_desc, msg, strlen(msg), 0) < 0){
        printf("msg received");
		return 0; 
	}
	return 1;
}

int readLine (char *lineBuffer){

	int i = 0;
	while (bufPtr < bufSize){
		if (buffer[bufPtr] == '\n'){
			lineBuffer[i] = '\0';
			bufPtr++;
			return 1;
		
		}else{
			lineBuffer[i++] = buffer[bufPtr++];
		}

		bufSize = recv(socket_desc, buffer, 1024, 0);
		bufPtr = 0;//'\0'?
		return i + readLine(&lineBuffer[i]);
	}
}
