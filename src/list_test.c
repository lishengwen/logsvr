#include <my_type.h>
#include <stdio.h>
#include <string.h>

static char *test = "hello world";

void str_test()
{
	my_str *strp = alloc_str(test, strlen(test));

	printf("content: %s, len: %d\n", STR_CONTENT(strp), STR_LENGTH(strp) + 1);

	free_str(strp);
}

