#include "config.h"
#include "comm.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_IP	"HOSTIP"
#define SERVER_PORT "HOSTPORT"


static char *s_config_file_path = NULL;
static config_t *configs = NULL;
extern char *g_config_file_path;

typedef void(*parse_handle_t)(const char *); 

static void parse_string_item(const char *expr);
static void parse_int_item(const char *expr);

typedef struct config_type_map_s {
	char *type;
	parse_handle_t handler;
} config_type_map_t;

static config_type_map_t config_map[2] = 
{
	{"string", parse_string_item},
	{"int", parse_int_item},
};

static void parse_string_item(const char *expr)
{
	char key[32];
	char val[32];

	char *buff = (char *)malloc(sizeof(char) * (strlen(expr)+ 1));
	memset(buff, 0, strlen(expr)+ 1);
	strncpy(buff, expr, strlen(expr));

	INIT_STR_ARR(key);
	INIT_STR_ARR(val);

	trim(buff);
	
	int pos = find_char_pos(buff, '=');
	//printf("pos: %d\n", pos);

	if (pos < 0) {
		free(buff);
		FATAL("LOGSVR: Wrong expr");
	}

	strncpy(key, buff, pos);
	strncpy(val, buff + pos + 1, strlen(buff) - pos + 1);

	free(buff);

	//printf("key: %s, val: %s\n", key, val);

	if (!strcmp(key, SERVER_IP)) {
		strncpy(configs->server_ip, val, sizeof(val));
	}
	// TODO more
}

static void parse_int_item(const char *expr)
{
	int ret;
	char key[32];
	char strval[32];
	int val;

	char *buff = (char *)malloc(sizeof(char) * (strlen(expr)+ 1));
	memset(buff, 0, strlen(expr)+ 1);

	strncpy(buff, expr, strlen(expr));

	INIT_STR_ARR(key);

	trim(buff);

	int pos = find_char_pos(buff, '=');
	//printf("pos: %d\n", pos);

	if (pos < 0) {
		free(buff);
		FATAL("LOGSVR: Wrong expr");
	}

	strncpy(key, buff, pos);
	strncpy(strval, buff + pos + 1, strlen(buff) - pos + 1);
	val = atoi(strval);

	free(buff);

	//printf("key: %s, val: %d\n", key, val);

	if (!strcmp(key, SERVER_PORT)) {
		configs->server_port = val;
	}

	// TODO more
}

static void parse_config_item(const char *buff)
{
	char *ptr = NULL;
	char type[16];
	int offset;
	int i;
	int map_sz;
	if (!configs) {
		return;
	}

	ptr = (char *)buff;
	INIT_STR_ARR(type);
	
	while (*ptr != ' ') {
		offset = ptr - buff;
		if (offset >= sizeof(type)) break;

		type[offset] = *ptr;
		++ ptr;
	}


	map_sz = sizeof(config_map) / sizeof(config_type_map_t);
	for (i = 0; i < map_sz; ++ i) {
		if (!strcmp(type, config_map[i].type)) {
			(config_map[i].handler)(buff + offset + 2);
			return;
		}
	}
}

void construct_config()
{
	FILE *fd;
	char buff[128];

	if (g_config_file_path) {
		strncpy(s_config_file_path, g_config_file_path, strlen(g_config_file_path));
	}
	else {
		s_config_file_path = "config.conf";
	}

	configs = (config_t *)malloc(sizeof(config_t));
	INIT_STR_ARR(configs->server_ip);
	configs->server_port = 0;

	fd = fopen(s_config_file_path, "r");

	if (fd <= 0) {
		printf("cann't open config file!\n");
		return;
	}

	while(fgets(buff, sizeof(buff), fd)) {
		if (strlen(buff) <= 1) continue;
		if (buff[0] == '#') continue;
		parse_config_item(buff);
		RESET_STR_ARR(buff);
	}

	printf("%s %d", configs->server_ip, configs->server_port);

	fclose(fd);
}

void destruct_config()
{
	if (configs) {
		free(configs);
	}
}

int get_config_port()
{
	return configs->server_port;
}

char *get_config_host()
{
	return configs->server_ip;
}

