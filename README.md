This is an examples code for socket programming

These are just basic sending and receiving message from client to server and back to client to echo a simple message. 

socket does not use secured layer

There are 3 examples:
echo_client connect with echo_server

echo_client2 connect with echo_server2

echo_client_hello connect with echo_server_hello

The binary application is located on the build folder and the source code located on the src folder

The Makefile is just an example build script that can be use to compile the source code. 

The source code will compile using GNU GCC or clang. 


![Socket Programming](https://github.com/htanama/Client-Server-Examples/blob/main/socket-programming.png)

 ([Watch this video](https://www.youtube.com/watch?v=cOeKykAYw-4))


Dive into code:

https://linux.die.net/man/2/accept
The accept() function:

```c
// int accept4(int sockfd, struct sockaddr *addr, socklen_t *addrlen, int flags);
accept(listenfd, (struct sockaddr *) &clientAddress, &clientLength);
```
`&clientAddress` is the address of the `clientAddress` variable, which is a struct of type `sockaddr_in`. This is a pointer to the structure, and it needs to be cast to `struct sockaddr *`, because the `accept()` function expects a pointer to a `struct sockaddr`, not a `struct sockaddr_in`.

 we are casting the address of the `clientAddress` variable to a `struct sockaddr *`, which is necessary for the
`accept()` function to work properly.

It's worth noting that the `accept()` function returns a new file descriptor that represents the accepted connection, and it also fills in the `sockaddr *` structure with the address of the client that connected to the server. The `clientLength` variable is used to store the length of the `sockaddr` structure that was filled in by the `accept()` function.