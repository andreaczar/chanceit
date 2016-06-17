#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
//#include <arpa/inet.h> //inet_addr
/**
*  Precondition: Player vs Network or AI vs Network has been called
*  Postcondition: Tells the client whether or not the connection was successful and connects if it worked.
*  Returns: A 1 if there was an error or a 0 if successful.
**/
int serverConnect (char *ip, int port);
/**
*  Precondition: Connection to the server has been made
*  Postcondition: Sends a char array of a message
*  Returns: 0 if successful and 1 if not
**/
int clientSend(char *msg);
/**
*  Precondition: Connection to the server has been made
*  Postcondition: Recieves a line/lines of text from the server and will update the client. 
*  Returns: A count of the number of bytes copied into the variable passed in if it's reached the end of the line
			or it reads more information in
**/
int clientRecv (char *lineBuffer);