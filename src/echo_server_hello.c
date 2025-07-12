// echo_server_hello.c
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>


#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 8 /*maximum number of client connections */

int main (int argc, char **argv)
{
    bool isConnecting = false;

    // hold file descriptor
    int connfd;

    struct sockaddr_in clientAddress, servaddr;

    // socklen_t, which is an unsigned opaque integral type of length of at least 32 bits. To forestall portability problems
    socklen_t clientLength;
    
    //creation of the socket
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);

    //preparation of the socket address 
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // bind socket to address. 
    int bind_result = bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    // listen for connections on a socket
    listen(listenfd, LISTENQ);

    printf("Server running...waiting for connections on port %d.\n", SERV_PORT);
    isConnecting = true;

    while (isConnecting) {
        char buf[MAXLINE];
        int n;
       
         clientLength = sizeof(clientAddress);
        //accept a connection on the socket
        connfd = accept(listenfd, (struct sockaddr *) &clientAddress, &clientLength);
        
      
        //receive and print messages from client
        while ((n = recv(connfd, buf, MAXLINE, 0)) > 0) {
            printf("Client sent: %s\n", buf);
            char *add_msg = "...Request is completed by the server\n";
            strcat(buf, add_msg);
            send(connfd, buf, strlen(buf), 0);
        }
        
        if (n < 0) {
            perror("read error");
            exit(1);
        }

        close(connfd);
    }
}

