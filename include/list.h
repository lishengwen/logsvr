#ifndef _LIST_H_
#define _LIST_H_

#include <stddef.h>

typedef struct list_head_s {
	struct list_head_s *prev, *next;
} list_head;

#define CONTAINER_OF(ptr, type, member) ({\
		const typeof(((type *)0)->member) *_tmptr = ptr;\
		(type *)(_tmptr - offset(type, member));\
	})

#define LIST_ENTRY(ptr, type, member) CONTAINER_OF(ptr, type, member)

#define INIT_LIST(name) {&name, &name}

#define _LIST_INSERT(elem, p, n) do {\
	elem->prev = p;\
	elem->next = n;\
	p->next = elem;\
	n->prev = elem;\
} while(0)

#define LIST_INSERT(elem, head)	_LIST_INSERT(elem, head, head->next)

#define LIST_INSERT_TAIL(elem, head) _LIST_INSERT(elem, head->prev, head)

#define LIST_EMPTY(head) (head == head->next)

#endif
