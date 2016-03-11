/**************************
 * MAUGER & SEYS - Nicolas
 * Tomchapache
 * 11 mar. 2016
 * response.h 
 **************************/

void send_status (FILE *client, int code, const char *reason_phrase);
void send_response (FILE *client, int code, const char *reason_phrase, const char *message_body);

