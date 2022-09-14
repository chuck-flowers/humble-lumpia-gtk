#ifndef __STRING_LIST_H
#define __STRING_LIST_H

#include <stddef.h>

typedef struct {
	char **elements;
	size_t length;
	size_t capacity;
} StringList;

StringList *string_list_new();

StringList *string_list_delete(StringList *sl);

void string_list_append(StringList *sl, char *element);

#endif
