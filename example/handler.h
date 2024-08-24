#ifndef _EXAMPLE_HANDLER_H
#define _EXAMPLE_HANDLER_H

#include "uhttpd.h"

void echo_handler(struct uh_connection *conn, int event);
void upload_handler(struct uh_connection *conn, int event);

#endif