#include "server.h"
#include <stdio.h>

#define PORT "4444"

int main() {
    if (initialize_winsock() != 0) {
        printf("Failed to initialize Winsock.\n");
        return 1;
    }

    SOCKET server = create_server_socket(PORT);
    if (server == INVALID_SOCKET) {
        printf("Failed to create server socket.\n");
        WSACleanup();
        return 1;
    }

    SOCKET client = wait_for_client(server);
    if (client == INVALID_SOCKET) {
        cleanup_server(client, server);
        return 1;
    }

    // Placeholder for communication
    printf("[+] Placeholder: ready for encrypted comms.\n");

    cleanup_server(client, server);
    return 0;
}
