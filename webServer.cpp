#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
int main() {
    // Step 1: Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080); // Port 8080
    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    listen(serverSocket, 5);   //5 concurrent connections 
    
    std::cout << "Server listening on port 8080..." << std::endl;

    while (true) {
        sockaddr_in clientAddress;
        socklen_t clientAddrSize = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddrSize);
        std::string response ="HTTP/1.1 200 OK\r\n";
        response += "Content-Type: text/html\r\n\r\n";
        response += "<html><body><h1>SERVER RUNNING</h1></body></html>\r\n";
        ssize_t bytesSent = send(clientSocket, response.c_str(), response.length(), 0);
        close(clientSocket);
    }
    close(serverSocket);

    return 0;
}
//check if port 8080 is running
