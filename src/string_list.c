#include <stddef.h>
#include <stdlib.h>

#include "logging.h"
#include "string_list.h"

#define INITIAL_CAPACITY 10
#define NEXT_CAPACITY(curr_cap) (curr_cap + 10)

void string_list_expand(StringList *sl, size_t min_cap);

StringList *string_list_new() {
	LOG_TRACE("string_list_new");

	StringList *sl = malloc(sizeof(StringList));
	sl->elements = malloc(sizeof(char*) * INITIAL_CAPACITY);
	sl->capacity = INITIAL_CAPACITY;
	sl->length = 0;

	return sl;
}

StringList *string_list_delete(StringList *sl) {
	LOG_TRACE("string_list_delete");

	for (size_t i = 0; i < sl->length; i++) {
		free(sl->elements[i]);
	}

	free(sl);

	return NULL;
}

void string_list_append(StringList *sl, char *element) {
	LOG_TRACE("string_list_append(%s)", element);

	const size_t curr_length = sl->length;
	const size_t new_length = curr_length + 1;

	const size_t curr_capacity = sl->capacity;
	if (new_length >= curr_capacity) {
		string_list_expand(sl, NEXT_CAPACITY(new_length));
	}

	sl->elements[sl->length++] = element;
}

void string_list_expand(StringList *sl, size_t new_capacity) {
	LOG_TRACE("string_list_expand(%ld)", new_capacity);

	// Allocate the new buffer
	char **old_elements = sl->elements;
	char **new_elements = malloc(sizeof(char *) * new_capacity);
	
	// Copy the current data
	for (size_t i = 0; i < sl->length; i++) {
		new_elements[i] = old_elements[i];
	}

	sl->elements = new_elements;
	free(old_elements);
}

