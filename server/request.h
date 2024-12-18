#ifndef REQUEST_H
#define REQUEST_H

#define URL_LEN 128

#define GET_STR "GET"
#define HEAD_STR "HEAD"

#define HTTP11_STR "HTTP/1.1"
#define HTTP10_STR "HTTP/1.0"

typedef enum request_method_t { BAD, GET, HEAD } request_method_t;

typedef struct request_t {
    request_method_t method;
    char url[URL_LEN];
} request_t;

int parse_req(request_t *req, char *buff);

#endif 
