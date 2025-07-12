#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define SERVER_PORT 3000

// this function declaration is optional, needed on my VIM edditor setting
int inet_pton(int af, const char *src, void *dst);
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
int close(int fd);

int main(int argc, char *argv[]){

    char message[100]="hello, client request";
    char receive_msg[100];

    //create socket 
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
       
    if(clientSocket < 0){
        perror("\x1b[31;1msocket connectionfailed! \n"); 
        exit(EXIT_FAILURE);
    }  
    
    // struct to hold server address info
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SERVER_PORT);
    
    // inet_pton: convert IPv4 and IPv6 addresses from text to binary form
    // int inet_pton(int af, const char *src, void *dst);
    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);


    if(connect(clientSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0){
        perror("\x1b[31;1mCONNECTION FAILED! \n");
        exit(EXIT_FAILURE);
    } 
    else{
        send(clientSocket, message, sizeof(message),0);            
    }
    
    recv(clientSocket, receive_msg, sizeof(receive_msg), 0);
    //ssize_t recv(int sockfd, void *buf, size_t len, int flags);    
    
    // display msg from server to client
    printf("\nServer sent: %s \n", receive_msg);
    
        
    // close connection
    close(clientSocket);


    return 0; 
}
