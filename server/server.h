#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>

int initialize_winsock();
SOCKET create_server_socket(const char *port);
SOCKET wait_for_client(SOCKET server_socket);
void cleanup_server(SOCKET client_socket, SOCKET server_socket);

#endif