#include "server.h"
#include <ws2tcpip.h>
#include <stdio.h>

int initialize_winsock() {
    WSADATA wsaData;
    return WSAStartup(MAKEWORD(2, 2), &wsaData);
}

SOCKET create_server_socket(const char *port) {
    struct addrinfo hints, *result = NULL;
    SOCKET ListenSocket = INVALID_SOCKET;
    int iResult;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    iResult = getaddrinfo(NULL, port, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed: %d\n", iResult);
        return INVALID_SOCKET;
    }

    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        return INVALID_SOCKET;
    }

    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        return INVALID_SOCKET;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, 1);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        return INVALID_SOCKET;
    }

    return ListenSocket;
}

SOCKET wait_for_client(SOCKET server_socket) {
    printf("Waiting for client...\n");
    SOCKET client = accept(server_socket, NULL, NULL);
    if (client == INVALID_SOCKET) {
        printf("accept failed: %d\n", WSAGetLastError());
    } else {
        printf("Client connected.\n");
    }
    return client;
}

void cleanup_server(SOCKET client_socket, SOCKET server_socket) {
    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();
}
