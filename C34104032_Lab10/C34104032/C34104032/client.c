#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080 // Port number
#define BUFFER_SIZE 1024 // Size of the buffer for communication

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0); // Create socket
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0}; // Buffer to hold data

    // Configure server address
    serv_addr.sin_family = AF_INET; // IPv4
    serv_addr.sin_port = htons(PORT); // Server port
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr); // Server IP address

    // Connect to the server
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    while (fgets(buffer, BUFFER_SIZE, stdin)) {
        send(sock, buffer, strlen(buffer), 0); // Send command to server
        memset(buffer, 0, BUFFER_SIZE); // Clear buffer
        read(sock, buffer, BUFFER_SIZE); // Read response from server
        printf("%s", buffer); // Print response
    }

    // Close the socket
    close(sock);
    return 0;
}

