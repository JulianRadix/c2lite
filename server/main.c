#include "server.h"
#include <stdio.h>
#include <string.h>

#define PORT "4444"

static void interactive(SOCKET c) {
    char cmd[1024];
    char buf[8192];
    for (;;) {
        printf("cmd> ");
        if (!fgets(cmd, sizeof cmd, stdin)) break;
        size_t len = strlen(cmd);
        if (cmd[len - 1] == '\n') cmd[len - 1] = '\0';
        if (send(c, cmd, (int)len, 0) <= 0) break;
        if (!strcmp(cmd, "exit")) break;
        int n = recv(c, buf, sizeof buf - 1, 0);
        if (n <= 0) break;
        buf[n] = '\0';
        puts(buf);
    }
}

int main(void) {
    if (initialize_winsock()) return 1;
    SOCKET srv = create_server_socket(PORT);
    if (srv == INVALID_SOCKET) return 1;
    SOCKET cli = wait_for_client(srv);
    if (cli != INVALID_SOCKET) interactive(cli);
    cleanup_server(cli, srv);
    return 0;
}
