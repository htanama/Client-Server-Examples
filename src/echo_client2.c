#include <stdio.h> // Include standard input/output library
#include <stdlib.h> // Include standard library for memory management and exit()
#include <string.h> // Include string library for operations like strlen()
#include <sys/socket.h> // Include socket library for creating sockets
#include <netinet/in.h> // Include internet protocol (IPv4) library

#define MAX_CLIENTS 10 // Define a constant for maximum number of clients (not used in this code)
#define BUFFER_SIZE 1024 // Define a constant for buffer size (used to receive data from server)

int main() {
    int clientSocket; // Declare a variable to store the socket file descriptor
    struct sockaddr_in serverAddress; // Declare a structure to hold server address information
    char receiveBuffer[BUFFER_SIZE]; // Declare a character array to store received data

    // Create a socket using TCP/IP protocol (SOCK_STREAM) with IPv4 addressing (AF_INET)
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) { // Check if socket creation failed
        perror("socket() failed"); // Print error message
        exit(EXIT_FAILURE); // Exit program with failure status
    }

    serverAddress.sin_family = AF_INET; // Set address family to IPv4
    serverAddress.sin_port = htons(8080); // Convert port number to network byte order and set it
    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr); // Convert IP address from string to binary format

    // Connect to the server at the specified port (8080) on localhost (127.0.0.1)
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) { // Check if connection failed
        perror("connect() failed"); // Print error message
        exit(EXIT_FAILURE); // Exit program with failure status
    }

    char userInput; // Declare a variable to store user's input

    while(1) {
        printf("\nEnter your message: "); // Prompt user for input
        char name[BUFFER_SIZE]; // Declare a character array to store user's input
        fgets(name, BUFFER_SIZE, stdin); // Read user's input from standard input

        // Remove newline character from input (in case it was added by fgets())
        int i = strlen(name) - 1;
        if (name[i] == '\n') {
            name[i] = '\0'; // Replace newline character with null terminator
        }

        printf("Sending message to server... "); // Prompt user for confirmation
        send(clientSocket, name, strlen(name), 0); // Send user's input to the server over the socket
        printf("Sent.\n"); // Print confirmation

        // Receive response from the server
        int receiveLength = recv(clientSocket, receiveBuffer, BUFFER_SIZE - 1, 0);
        if (receiveLength < 0) { // Check if receiving data failed
            perror("recv() failed"); // Print error message
            exit(EXIT_FAILURE); // Exit program with failure status
        }
        receiveBuffer[receiveLength] = '\0'; // Null-terminate received string
        printf("Received: %s\n", receiveBuffer); // Print received response from server

        printf("\nDo you want to continue? (y/n): "); // Prompt user for continuation decision
        scanf(" %c", &userInput); // Read single character input from standard input
        getchar(); // Consume newline character left in buffer by scanf()

        if (userInput == 'n' || userInput == 'N') { // Check if user wants to stop sending messages
            break; // Exit loop and terminate program
        }
    }

    close(clientSocket); // Close the socket to release system resources
    return 0; // Return successful exit status
}
