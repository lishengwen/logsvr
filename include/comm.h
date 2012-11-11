#ifndef _COMM_H_
#define _COMM_H_

#include <stdio.h>

// TODO log
#define INIT_STR_ARR(arr) bzero(arr, sizeof(arr))
#define RESET_STR_ARR(arr) INIT_STR_ARR(arr)

#define FATAL(fmt...) do {\
	printf(fmt);\
	exit(0);\
} while(0)


#endif
	
