#include "uhttpd.h"

static void test_handler(struct uh_connection *conn, int event)
{
    struct uh_str path;

    if (event != UH_EV_COMPLETE)
        return;

    path = conn->get_path(conn);

    conn->send_head(conn, 200, -1, NULL);
    conn->printf(conn, "Path: %.*s\n", (int)path.len, path.p);
    conn->end_response(conn);
}

struct uh_plugin_handler uh_plugin_handler = {
    .path = "^/test$",
    .handler = test_handler
};
