#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_CLIENTS 10

// close file descriptor - unistd.h
// int close(int fd);
void close(int clientSocket);

void handleClient(int clientSocket) {
    bool isConnecting=true;

    // Receive message from the client using recv()
    char receiveBuffer[1024];
    int receiveMessageLength = recv(clientSocket, receiveBuffer, 1024, 0);
    if (receiveMessageLength < 0) {
        // Handle error during data reception
        perror("recv()");
        return;
    }

    printf("Received: %s\n", receiveBuffer);

    // Send response back to the client using send()
    char *response = "Hello, Client!";
    int sendMessageLength = strlen(response);
    
    if (send(clientSocket, response, sendMessageLength, 0) < 0) {
        // Handle error during data transmission
        perror("send()");
        return;
    }

    printf("Sent: %s\n", response);
    printf("waiting from client request ...\n");     
    
    if(isConnecting == false){
        // Close the client socket to release system resources
        close(clientSocket);
    }
}

int main() {
    // Initialize values for the server address and port number
    int serverPort = 8080;

    // Create a socket using TCP/IP protocol (SOCK_STREAM) with IPv4 addressing (AF_INET)
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        // Handle error during socket creation
        perror("socket()");
        exit(1);
    }

    // Set up the server address structure for binding
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;       // IPv4 addressing
    serverAddress.sin_port = htons(serverPort);   // Convert port number to network byte order

    // Bind the socket to the server's IP address and port
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        // Handle error during binding
        perror("bind()");
        exit(1);
    }

    // Listen for incoming connections from clients
    if (listen(serverSocket, MAX_CLIENTS) < 0) {
        // Handle error during listening
        perror("listen()");
        exit(1);
    }

    printf("Server listening on port %d...\n", serverPort);

    while (1) {
        // Accept an incoming connection from a client
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);
        if (clientSocket < 0) {
            // Handle error during accepting
            perror("accept()");
            continue;
        }

        printf("Connected to client...\n");

        // Handle the client's connection in a separate thread or process
        handleClient(clientSocket);

 //       break; // Break out of the loop after handling one client connection
    }

    return 0;
}
