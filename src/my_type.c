#include <my_type.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

my_str *alloc_str(const char *content, int len)
{
	my_str *strp = (my_str *)malloc(sizeof(*strp) + len);
	strp->len = len;
	strp->type = T_STRING;
	memcpy(strp->ptr, content, len);

	return strp;
}

void free_str(my_str *strp)
{
	if (strp) {
		free(strp);
	}
}

