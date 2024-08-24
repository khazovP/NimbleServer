#ifndef LIBUHTTPD_FILE_H
#define LIBUHTTPD_FILE_H

#include <sys/stat.h>

#include "connection.h"

struct path_info {
    const char *root;
    const char *phys;
    const char *name;
    const char *info;
    struct stat *st;
};

struct path_info *parse_path_info(struct uh_connection_internal *conn);

void serve_file(struct uh_connection *conn);
void download_file(struct uh_connection *conn, const char *path, const char *filename);

#endif
