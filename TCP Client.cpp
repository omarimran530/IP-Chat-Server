//
//  TCP Client.cpp
//  IP Chat Server
//
//  Created by Omar Imran on 11/12/23.
//

#include "TCP Client.hpp"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int main() {
    int sock = 0 // Socket descriptor for client
    struct sockaddr_in serv_addr; // Structure to hold the server address
    const char *message = "Hello from client"; // Message to send to server
    char buffer[1024] = {0}; // Buffer to store message from server
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "\n Socket creation error \n";
        return -1;
    }
    
    serv_addr.sin_family = AF_INET; //IPv4 protocol
    serv_addr.sin_port = htons(8080); // Port number, converted to network byte order
    
    // Convert IPv4 and IPv6 addresses rom text to binary
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cout << "\n Invalid address/ Address not supported \n";
        return -1;
    }
    
    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "\n Connection Failed \n";
        return -1;
    }
    
    // Send message to server
    send(sock, message, strlen(message), 0); // Send data to server
    
    // Read server response
    read(sock, buffer, 1024); // Read data into buffer
    std::cout << "Message from server: " << buffer << std::endl;
    
    // Close the socket
    close(sock); // Close client socket
    
    return 0;
}
