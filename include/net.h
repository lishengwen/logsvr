#ifndef _NET_H_
#define _NET_H_

#include "my_type.h"

#include <sys/socket.h>

typedef struct lg_socket_s {
	int sockfd;

} lg_socket_t;

typedef struct lg_connection_s {
	lg_socket_t socket;

} lg_connection_t;

typedef lg_port_t int;


// net.c
lg_socket_t lg_net_socket(int family, int type, int protocol);
int lg_net_bind(lg_str_t host, lg_port_t port, lg_socket_t * socket_p);
// TODO

#endif
