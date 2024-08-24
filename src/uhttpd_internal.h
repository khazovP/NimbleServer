#ifndef LIBUHTTPD_UHTTPD_INTERNAL_H
#define LIBUHTTPD_UHTTPD_INTERNAL_H

#include <arpa/inet.h>

#include "uhttpd.h"
#include "list.h"

#ifdef SSL_SUPPORT
#include "ssl/ssl.h"
#endif

struct uh_server_internal;
struct uh_connection_internal;

struct uh_path_handler {
    uh_path_handler_prototype handler;
    struct list_head list;
    uint8_t flags;
    uint8_t len;
    char path[0];
};

struct uh_plugin {
    struct uh_plugin_handler *h;
    void *dlh;
    uint8_t flags;
    uint8_t len;
    const char *path;
    struct list_head list;
};

struct uh_listener {
    int sock;
    bool ssl;
    struct ev_io ior;
    struct list_head list;
    struct uh_server_internal *srv;
};

struct uh_server_internal {
    struct uh_server com;
    char *docroot;
    char *index_page;
    bool reuse_port;
    bool https_redirect;
    struct ev_loop *loop;
    void (*conn_closed_cb)(struct uh_connection *conn);
    void (*default_handler)(struct uh_connection *conn, int event);
#ifdef SSL_SUPPORT
    struct ssl_context *ssl_ctx;
#endif
    struct list_head listeners;
    struct list_head handlers;
    struct list_head plugins;
    struct list_head conns;
};

#endif
