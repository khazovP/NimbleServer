#include <stddef.h>
#include <stdbool.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <ctype.h>

#include "utils.h"

const char *saddr2str(const struct sockaddr *addr, char buf[], int len, int *port)
{
    if (addr->sa_family == AF_INET) {
        struct sockaddr_in *sin = (struct sockaddr_in *)addr;
        *port = ntohs(sin->sin_port);
        inet_ntop(AF_INET, &sin->sin_addr, buf, len);
    } else {
        struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)addr;
        *port = ntohs(sin6->sin6_port);
        inet_ntop(AF_INET6, &sin6->sin6_addr, buf, len);
    }

    return buf;
}

bool support_so_reuseport()
{
    bool ok = false;
    int on = 1;
    int sock;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (!setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(int)))
        ok = true;

    close(sock);

    return ok;
}

int urldecode(char *buf, int blen, const char *src, int slen)
{
    int i;
    int len = 0;

#define hex(x) \
    (((x) <= '9') ? ((x) - '0') : \
        (((x) <= 'F') ? ((x) - 'A' + 10) : \
            ((x) - 'a' + 10)))

    for (i = 0; (i < slen) && (len < blen); i++) {
        if (src[i] != '%') {
            buf[len++] = src[i];
            continue;
        }

        if (i + 2 >= slen || !isxdigit(src[i + 1]) || !isxdigit(src[i + 2]))
            return -2;

        buf[len++] = (char)(16 * hex(src[i+1]) + hex(src[i+2]));
        i += 2;
    }
    buf[len] = 0;

    return (i == slen) ? len : -1;
}

const char *canonpath(char *path, size_t *len)
{
    char *resolved = path;
    const char *p = path;
    int rel = 0;

    while ((*len)--) {
        if (*p != '/')
            goto next;

        /* skip repeating / */
        if (p[1] == '/') {
            p++;
            continue;
        }

        /* /./ or /../ */
        if (p[1] == '.') {
            /* skip /./ */
            if (p[2] == '/' || p[2] == '\0') {
                p += 2;
                continue;
            }

            /* collapse /x/../ */
            if (p[2] == '.' && (p[3] == '/' || p[3] == '\0')) {
                p += 3;
                continue;
            }
        }

next:
        *resolved++ = *p++;
        rel++;
    }

    *resolved = '\0';
    *len = rel;

    return path;
}
