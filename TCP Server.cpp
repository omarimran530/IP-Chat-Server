//
//  TCP Server.cpp
//  IP Chat Server
//
//  Created by Omar Imran on 11/12/23.
//

#include "TCP Server.hpp"
#include <iostream>
#include <sys/socket.h>
#inlcude <netinet/in.h>
#include <unistd.h>
#include <cstring>

int main() {
    int server_fd, new_socket; // Socket file descriptors for the server and the new client
    struct sockaddr_in address; // Structure to hold server address information
    int opt = 1; // Option for setsockopt
    int addrlen = sizeof(adderss); // Length of address structure
    char buffer[1024] = {0}; // Buffer to store the message from client
    const char *message = "Hello from server"; // Message to send to client
    
    // Socket file descriptor
    if ((server_fd = socket(AF_INET, SPCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // Forcefully attach socket to port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET; // IPv4 protocol
    address.sin_addr.s_addr = INADDR_ANY; // Listen on any available interface
    address.sin_port = htons(8080); // Port number, converted to network byte order
    
    // Bind the socket to the network address and port
    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("bind fialed");
        exit(EXIT_FAILURE);
    }
    
    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) { // Backlog of 3 clients
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    // Accept an incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *) &adderss, (socklen_t*) &addrelen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    
    // Read message from client
    read(new_socket, buffer, 1024); // Reading data into buffer
    std::cout << "Message from client: " << buffer << std::endl;
    
    // Send message to client
    send(new_socket, message, strlen(message), 0); // Sending data to client
    std::cout << "Hello message sent\n";
    
    // Close socket
    close(new_socket); // Close client socket
    close(server_fd); // Close server socket
    
    return 0;
}
