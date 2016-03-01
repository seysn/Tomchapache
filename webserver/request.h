/**************************
 * MAUGER & SEYS - Nicolas
 * Tomchapache
 * 01 mar. 201
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
    char *url;
} http_request;

char *fgets_or_exit (char *buffer, int size, FILE * stream);
/*
int parse_http_request (const char *request_line, http_request *request);
void skip_header (FILE *client);

void send_status (FILE *client, int code, const char *reason_phrase);
void send_reponse (FILE *client, int code, const char *reason_phrase,
     const char *message_body);
*/
