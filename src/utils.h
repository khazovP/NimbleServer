#ifndef LIBUHTTPD_UTILS_H
#define LIBUHTTPD_UTILS_H

#include <stddef.h>
#include <stdbool.h>
#include <inttypes.h>
#include <sys/socket.h>

const char *saddr2str(const struct sockaddr *addr, char buf[], int len, int *port);

bool support_so_reuseport();

/*
** blen is the size of buf; slen is the length of src.  The input-string need
** not be, and the output string will not be, null-terminated.  Returns the
** length of the decoded string, -1 on buffer overflow, -2 on malformed string.
*/
int urldecode(char *buf, int blen, const char *src, int slen);

const char *canonpath(char *path, size_t *len);

#endif
