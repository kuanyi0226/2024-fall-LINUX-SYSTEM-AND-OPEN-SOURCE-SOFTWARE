#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <math.h>

#define PORT 8080 // Port number 
#define BUFFER_SIZE 1024 // Size of the buffer for communication

// Function to handle a single client connection
void handle_client(int client_sock) {
    char buffer[BUFFER_SIZE];
    int num1, num2, result;

    while (1) {
        memset(buffer, 0, BUFFER_SIZE); // Clear the buffer
        read(client_sock, buffer, BUFFER_SIZE); // Read the client's command

        // Handle "add a b" command
        if (strncmp(buffer, "add", 3) == 0) {
            sscanf(buffer, "add %d %d", &num1, &num2); 
            result = num1 + num2; // Calculate sum
            snprintf(buffer, BUFFER_SIZE, "%d\n", result); // Format the result
        }
        // Handle "abs a" command
        else if (strncmp(buffer, "abs", 3) == 0) {
            sscanf(buffer, "abs %d", &num1); 
            result = abs(num1); // Calculate absolute value
            snprintf(buffer, BUFFER_SIZE, "%d\n", result); // Format the result
        }
        // Handle "mul a b" command
        else if (strncmp(buffer, "mul", 3) == 0) {
            sscanf(buffer, "mul %d %d", &num1, &num2);
            result = num1 * num2;// Calculate the product
            snprintf(buffer, BUFFER_SIZE, "%d\n", result); // Format the result
        }
        // Handle "kill" command
        else if (strncmp(buffer, "kill", 4) == 0) {
            snprintf(buffer, BUFFER_SIZE, "\n");// Respond with a newline
            send(client_sock, buffer, strlen(buffer), 0); // Send response
            close(client_sock);// Close client socket
        }
        // Handle unsupported commands
        else {
            snprintf(buffer, BUFFER_SIZE, "Hello\n"); // Respond "Hello" 
        }

        // Send the response to the client
        send(client_sock, buffer, strlen(buffer), 0);
    }
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0); // Create a socket
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Configure server address
    address.sin_family = AF_INET; // IPv4
    address.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP address
    address.sin_port = htons(PORT); // Server port

    // Bind the socket to the specified port and IP address
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    // Start listening for incoming connections
    listen(server_fd, 3); //at most 3 

    // Accept and handle incoming client connections
    while (1) {
        int client_sock = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen); // Accept a connection
        handle_client(client_sock); // Handle the client's requests
    }

    return 0;
}

