#ifndef SERVER_H
#define SERVER_H

#include "thread_pool.h"
#include <poll.h>

#define HOST_SIZE 16
#define THREAD_NUM 10
#define PATH_NUM 256
#define HEADER_LEN 128

typedef struct server_t {
    char host[HOST_SIZE];
    int port;

    struct pollfd *clients;
    long cl_num;

    int listen_sock;
    tpool_t *pool;

    char *wd;
} server_t;

server_t *new_http_server(char *host, int port, int thread_num);

int run_http_server_t(server_t *server);

void free_http_server_t(server_t *server);

#endif
