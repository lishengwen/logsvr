#ifndef _CONFIG_H_
#define _CONFIG_H_

typedef struct config_s {
	char server_ip[256];
	unsigned short server_port;
} config_t;

char *get_config_host();
int get_config_port();
void construct_config();

#endif
