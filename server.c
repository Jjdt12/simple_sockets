#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 

    char sendBuff[1025];
    time_t ticks; 

	// Call socket to create a named socket in the kernel
	// AF_INET - IPV4 addresses
	// SOCK_STREAM - 
	// 0 - let the kernel select the protocol (default protocol TCP)
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET; // family
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // address to listen on
    serv_addr.sin_port = htons(5000); // port to listen on for connections 

	// Assigns the details from serv_addr struct to the socket created
	// by socket() (listenfd)
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 


	// Max number of client connections (10) to queue on the listenfd socket 
    listen(listenfd, 10); 

	// Infite loop, server always runs
    while(1)
    {
		// Wait for connection, when connection -> tcp handshake. 
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 

        ticks = time(NULL);
		// Send the time to connected client
        snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
        write(connfd, sendBuff, strlen(sendBuff)); 

        close(connfd);
		// A little snooze here to reduce CPU usage
        sleep(1);
     }
}
