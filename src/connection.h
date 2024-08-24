#ifndef LIBUHTTPD_CONNECTION_H
#define LIBUHTTPD_CONNECTION_H

#include <arpa/inet.h>

#include "uhttpd_internal.h"
#include "buffer.h"
#include "cgi.h"

#define UHTTPD_CONNECTION_TIMEOUT   30.0
#define UHTTPD_MAX_HEADER_NUM       50

#define CONN_F_SEND_AND_CLOSE       (1 << 0)    /* Push remaining data and close  */
#define CONN_F_CLOSED               (1 << 1)    /* closed  */
#define CONN_F_SSL_HANDSHAKE_DONE   (1 << 2)    /* SSL hanshake has completed */

struct uh_server_internal;

struct uh_request {
    size_t length;  /* The total length of the request which still remain in buffer */
    struct {
        ssize_t offset;
        size_t length;
    } url;

    int header_num;
    bool last_was_header_value;
    struct {
        struct {
            ssize_t offset;
            size_t length;
        } field;
        struct {
            ssize_t offset;
            size_t length;
        } value;
    } headers[UHTTPD_MAX_HEADER_NUM];

    struct {
        bool consumed;  /* Indicates whether the extract_body is called */
        ssize_t offset;
        size_t length;
    } body;
};

struct uh_response {
    bool chunked;
};

struct uh_connection_internal {
    struct uh_connection com;
    struct list_head list;
    int sock;
    void *ssl;
    uint8_t flags;
    struct {
        int fd;
        uint64_t size;
    } file;
    uint8_t closed;
    size_t refcount;
    struct ev_io ior;
    struct ev_io iow;
    struct buffer rb;
    struct buffer wb;
    ev_tstamp activity;
    struct ev_timer timer;
    struct uh_request req;
    struct uh_response resp;
    struct uh_cgi *cgi;
    struct uh_listener *l;
    union {
        struct sockaddr     sa;
        struct sockaddr_in  sin;
        struct sockaddr_in6 sin6;
    } saddr; /* server address */
    union {
        struct sockaddr     sa;
        struct sockaddr_in  sin;
        struct sockaddr_in6 sin6;
    } paddr; /* peer address */
    struct http_parser parser;
    struct http_parser_url url_parser;
    void (*handler)(struct uh_connection *conn, int event);
};

void uh_new_connection(struct uh_listener *l, int sock, struct sockaddr *addr);

void conn_free(struct uh_connection_internal *conn);

#endif
