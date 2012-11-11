#include "util.h"
#include <string.h>
#include <stdio.h>

int find_char_pos(const char *buff, char tar)
{
	if (!buff) return -1;

	char *ptr = (char *)buff;
	while (*ptr != '\0') {
		if (*ptr == tar) {
			return ptr - buff;
		}

		++ ptr;
	}

	return -1;
}

void ltrim(char *buff)
{
	char *ptr = buff;
	while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n') ++ ptr;

	strcpy(buff, ptr);
}

void rtrim(char *buff)
{
	int len = strlen(buff) - 1;
	while ((buff[len] == ' ' || 
				buff[len] == '\t' || 
				buff[len] == '\n' ||
				buff[len] == '\r') && 
			len >= 0) -- len;

	buff[len + 1] = '\0';
}

void trim(char *buff)
{
	ltrim(buff);
	rtrim(buff);
}

