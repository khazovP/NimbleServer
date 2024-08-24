#ifndef LIBUHTTPD_CGI_H
#define LIBUHTTPD_CGI_H

#include "connection.h"

#define CGI_TIMEOUT 60

struct uh_cgi {
    struct uh_connection *conn;
    struct buffer rb;
    struct buffer wb;
    struct ev_io ior;
    struct ev_io iow;
    struct ev_timer tmr;
    struct ev_child proc;
    bool header_end;
    bool skip_data;
    int status_code;
    char status_msg[256];
    struct buffer headers;
    uint64_t content_length;
};

void serve_cgi(struct uh_connection *conn, int event);
void cgi_free(struct uh_connection_internal *conn);

#endif
