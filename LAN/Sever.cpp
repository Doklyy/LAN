#include<iostream>
#include<string>
#include<winsock2.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(54000);
    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, SOMAXCONN);
    std::cout << "Server dang cho ket noi..." << std::endl;
    sockaddr_in clientAddr;
    int clientSize = sizeof(clientAddr);
    SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);
    std::cout << " Client da ket noi!" << std::endl;
    char buffer[4096];
    while (true) {
        ZeroMemory(buffer, 4096);
        int bytesReceived = recv(clientSocket, buffer, 4096, 0);
        if (bytesReceived == SOCKET_ERROR) {
            std::cerr << "Loi khi nhan du lieu!" << std::endl;
            break;
        }
        if (bytesReceived == 0) {
            std::cout << "Client da ngat ket noi!" << std::endl;
            break;
        }
        std::cout << "Client:" << std::string(buffer, 0, bytesReceived) << std::endl;
        std::string response;
        std::cout << "Sever:";
        std::getline(std::cin, response);
        send(clientSocket, response.c_str(), response.size()+ 1, 0);
    }
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
