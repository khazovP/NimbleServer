#ifndef LIBUHTTPD_MIMETYPES_H
#define LIBUHTTPD_MIMETYPES_H

struct mimetype {
    const char *extn;
    const char *mime;
};

const char *file_mime_lookup(const char *path);

#endif
