#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h> 

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(54000);  
    if (inet_pton(AF_INET, "127.0.0.1", &(serverAddr.sin_addr)) <= 0) {
        std::cerr << "Lỗi: Địa chỉ IP không hợp lệ!" << std::endl;
        return -1;
    }
    int connectResult = connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    if (connectResult == SOCKET_ERROR) {
        std::cerr << "Không thể kết nối đến server!" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    std::cout << "Đã kết nối đến server!" << std::endl;
    char buffer[4096];
    while (true) {
        std::string userInput;
        std::cout << "Client: ";
        std::getline(std::cin, userInput);

        int sendResult = send(clientSocket, userInput.c_str(), userInput.size() + 1, 0);
        if (sendResult == SOCKET_ERROR) {
            std::cerr << "Gửi tin nhắn thất bại!" << std::endl;
            break;
        }
        ZeroMemory(buffer, 4096);
        int bytesReceived = recv(clientSocket, buffer, 4096, 0);
        if (bytesReceived > 0) {
            std::cout << "Server: " << std::string(buffer, 0, bytesReceived) << std::endl;
        }
    }
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
