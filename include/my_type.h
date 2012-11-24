#ifndef _MY_TYPE_H_
#define _MY_TYPE_H_

#define T_STRING	(0)
#define T_INT		(1)
#define T_ARRAY		(2)

typedef struct my_str_s {
	int len;
	int type;
	char ptr[0];
} my_str;

typedef lg_str_t my_str;


#define STR_CONTENT(strp) (char *)(strp + 1)
#define STR_LENGTH(strp)  (*(int *)(strp))

my_str *alloc_str(const char *content, int len);
void free_str(my_str *strp);

#endif

