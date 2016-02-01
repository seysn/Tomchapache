/***********************
 * MAUGER & SEYS Nicolas
 * Tomchapache
 * 01 feb. 2016
 * socket.h
***********************/

int socket(int domain, int type, int protocol);
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int listen(int sockfd, int backlog);
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
