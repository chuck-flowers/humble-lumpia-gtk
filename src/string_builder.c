#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logging.h"
#include "string_builder.h"

#define DEFAULT_BUFFER_SIZE 10
#define NEXT_CAPACITY(current_length) (current_length + 10)

void string_builder_expand_capacity(StringBuilder *sb, const size_t min_cap);

StringBuilder *string_builder_new() {
	LOG_TRACE("string_builder_new");

	StringBuilder *sb = malloc(sizeof(StringBuilder));
	sb->buffer = malloc(sizeof(char) * DEFAULT_BUFFER_SIZE);
	sb->capacity = DEFAULT_BUFFER_SIZE;
	sb->length = 0;

	return sb;
}

StringBuilder *string_builder_delete(StringBuilder *sb) {
	LOG_TRACE("string_builder_delete");

	free(sb->buffer);
	free(sb);
	return NULL;
}

char *string_builder_delete_and_take(StringBuilder *sb) {
	LOG_TRACE("string_builder_delete_and_take");

	char *buffer = sb->buffer;
	free(sb);

	return buffer;
}

void string_builder_append(StringBuilder *sb, const char *new_buffer) {
	const size_t new_buffer_length = strlen(new_buffer);
	string_builder_append_length(sb, new_buffer, new_buffer_length);
}

void string_builder_append_length(StringBuilder *sb, const char *to_append, size_t to_append_length) {
	LOG_TRACE("string_builder_append_length(%.5s, %ld)", to_append, to_append_length);

	const size_t curr_length = sb->length;
	const size_t new_length = curr_length + to_append_length;
	const size_t curr_capacity = sb->capacity;

	// If the resulting length is to great, expand.
	if (new_length >= curr_capacity) {
		string_builder_expand_capacity(sb, NEXT_CAPACITY(new_length));
	}

	// Copy the bytes into the string builder
	char *write_start = sb->buffer + sb->length;
	memcpy(write_start, to_append, to_append_length);

	// Update the other fields of the string builder
	sb->length = new_length;
	sb->buffer[new_length] = '\0';
}

void string_builder_clear(StringBuilder *sb) {
	LOG_TRACE("string_builder_clear");

	sb->length = 0;
	sb->buffer[sb->length] = '\0';
}

char *string_builder_clone(StringBuilder *sb) {
	LOG_TRACE("string_builder_clone");

	const size_t length = sb->length;

	// Create the clone
	char *clone = malloc(length + 1 * sizeof(char));
	memcpy(clone, sb->buffer, length);

	// Ensure it's NUL terminated
	clone[length] = '\0';

	return clone;
}

void string_builder_expand_capacity(StringBuilder *sb, const size_t new_capacity) {
	LOG_TRACE("string_builder_expand_capacity(%ld)", new_capacity);

	// Allocate the new buffer
	char *old_buffer = sb->buffer;
	char *new_buffer = calloc(new_capacity, sizeof(char));

	// Copy existing data to the new buffer
	memcpy(new_buffer, old_buffer, sb->length);
	sb->buffer[sb->length] = '\0';

	// Update the struct with the new memory
	sb->buffer = new_buffer;
	sb->capacity = new_capacity;

	// Clean up the old memory
	free(old_buffer);
}

