#ifndef SOCKET_POLL_H
#define SOCKET_POLL_H

#include "logger.h"
#include "server.h"

#define SIZE 1024
#define MAX_CLIENTS 100

int creat_socket(int port, char *host);
int wait_client(server_t *server);

#endif
