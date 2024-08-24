#ifndef LIBUHTTPD_HANDLER_H
#define LIBUHTTPD_HANDLER_H

static inline void file_handler(struct uh_connection *conn, int event)
{
    if (event != UH_EV_COMPLETE)
        return;

    conn->serve_file(conn);
}

static inline void cgi_handler(struct uh_connection *conn, int event)
{
    conn->serve_cgi(conn, event);
}

#endif
