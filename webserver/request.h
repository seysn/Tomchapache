/**************************
 * MAUGER & SEYS - Nicolas
 * Tomchapache
 * 01 mar. 2016
 * request.h
 **************************/

enum http_method {
     HTTP_GET,
     HTTP_UNSUPPORTED,
};

typedef struct {
    enum http_method method;
    int major_version;
    int minor_version;
    char url[512];
} http_request;

char *fgets_or_exit (char *buffer, int size, FILE * stream);
int parse_http_request (const char *request_line, http_request *request);
void skip_header (FILE *client);
char *rewrite_url (char *url);
int check_and_open (const char *url, const char *document_root);
