#include "config.h"
#include <stdio.h>

char *g_config_file_path = NULL;
void str_test();

int main(int argc, char *argv[])
{
	construct_config();
	str_test();
	return 1;
}
