#ifndef __STRING_BUILDER_H
#define __STRING_BUILDER_H

#include <stddef.h>
#include <stdio.h>

typedef struct {
	/** The pointer to the start of the string buffer */
	char *buffer;
	/** The number of bytes currently stored, excluding the NUL terminator */
	size_t length;
	/** The total allocated space of the string buffer, including space for the NUL terminator */
	size_t capacity;
} StringBuilder;

/**
 * Creates and initializes a new StringBuilder struct
 */
StringBuilder *string_builder_new();

/**
 * Totally deletes a StringBuilder struct
 */
StringBuilder *string_builder_delete(StringBuilder *sb);

/**
 * Deletes a StringBuilder struct except for its inner buffer
 */
char *string_builder_delete_and_take(StringBuilder *sb);

/**
 * Appends a NUL terminated string to the end of the StringBuilder.
 */
void string_builder_append(StringBuilder *sb, const char *buffer);

/**
 * Appends a specified number of bytes from a buffer to the end of the
 * StringBuilder.
 */
void string_builder_append_length(StringBuilder *sb, const char *buffer, size_t length);

/**
 * Softs deletes the content of the StringBuilder
 */
void string_builder_clear(StringBuilder *sb);

/**
 * Makes a copy of the current state of the StringBuilder's inner string.
 */
char *string_builder_clone(StringBuilder *sb);

#endif

