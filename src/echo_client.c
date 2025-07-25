#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define TRUE 1
#define FALSE 0

int
main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr;
    char sendline[MAXLINE], recvline[MAXLINE];
    char isConnected = FALSE;
        
    //Creation of the socket
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port =  htons(SERV_PORT); //convert to big-endian order
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    //basic check of the arguments
    //additional checks can be inserted
    /*
    if (argc !=2) {
        perror("Usage: TCPClient <IP address of the server");
        exit(1);
    }*/

    //Create a socket for the client
    //If sockfd<0 there was an error in the creation of the socket
    if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
        perror("Problem in creating the socket");
        exit(2);
    }

    //Creation of the socket
    // memset(&servaddr, 0, sizeof(servaddr));
    //servaddr.sin_family = AF_INET;
    //servaddr.sin_port =  htons(SERV_PORT); //convert to big-endian order
    //inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);


    //Connection of the client to the socket
    // (struct sockaddr*)&servaddr : cast the entire sockaddr_in to sockaddr*
    //
    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
        perror("Problem in connecting to the server");
        exit(3);
    }
    else{ 
       printf("connected\n");
       isConnected = TRUE;
    }
    
    
    while (isConnected) {      
        printf("Enter your message: "); 
        fgets(sendline, MAXLINE, stdin);           

        send(sockfd, sendline, strlen(sendline), 0);

        if (recv(sockfd, recvline, MAXLINE,0) == 0){
        //error: server terminated prematurely
        perror("The server terminated prematurely");
        exit(4);
        }
        printf("%s", "String received from the server: ");
        fputs(recvline, stdout);
               
        
    }

    exit(0);
}
