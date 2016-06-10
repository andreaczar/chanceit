//Socket.c
//#include stuff here
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h> //inet_add

static int socket_desc;
static char buffer [1024];
static int bufPtr = 0;
static int bufSize = 0;
/*
struct sockaddr_in {
    short            sin_family;   // e.g. AF_INET, AF_INET6
    unsigned short   sin_port;     // e.g. htons(3490)
    struct in_addr   sin_addr;     // see struct in_addr, below
    char             sin_zero[8];  // zero this if you want to
};
 
struct in_addr {
    unsigned long s_addr;          // load with inet_pton()
};
 
struct sockaddr {
    unsigned short    sa_family;    // address family, AF_xxx
    char              sa_data[14];  // 14 bytes of protocol address
};
*/
int serverConnect (char *IP, int port){

	//Basic C socket connection stuff
	//D2L tutorial for socketConnect
	//Return 1 = conn successful, 0 = error
	struct sockaddr_in server;
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
         
    server.sin_addr.s_addr = inet_addr(&IP);
    server.sin_family = AF_INET;
    server.sin_port = htons( port );
 
    //Connect to remote server
    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }
     
    puts("Connected");
    return 0;
	
}

int server_send(char * msg){

	if(send(socket_desc, msg, strlen(msg), 0) < 0){
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


}