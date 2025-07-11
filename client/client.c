#define WIN32_LEAN_AND_MEAN
#include "client.h"
#include <ws2tcpip.h>
#include <stdio.h>

int initialize_winsock(void) {
    WSADATA wsa;
    return WSAStartup(MAKEWORD(2,2), &wsa);
}

SOCKET connect_to_server(const char *ip, const char *port) {
    struct addrinfo hints = {0}, *res = NULL;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if (getaddrinfo(ip, port, &hints, &res) != 0)
        return INVALID_SOCKET;

    SOCKET s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (s == INVALID_SOCKET) { freeaddrinfo(res); return INVALID_SOCKET; }

    if (connect(s, res->ai_addr, (int)res->ai_addrlen) == SOCKET_ERROR) {
        closesocket(s); s = INVALID_SOCKET;
    }

    freeaddrinfo(res);
    return s;
}

void cleanup_client(SOCKET s) {
    closesocket(s);
    WSACleanup();
}
