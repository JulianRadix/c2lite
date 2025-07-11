#ifndef CLIENT_H
#define CLIENT_H
#include <winsock2.h>

int  initialize_winsock(void);
SOCKET connect_to_server(const char *ip, const char *port);
void cleanup_client(SOCKET s);

#endif
