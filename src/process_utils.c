#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logging.h"
#include "process_utils.h"
#include "string_builder.h"
#include "string_list.h"

#define BUFFER_SIZE 100

StringList *runProcess(const char *cmd) {
	LOG_TRACE("runProcess(%s)", cmd);

	StringList *ol = string_list_new();

	// Run the program
	FILE *ps_out = popen(cmd, "r");
	if (ps_out == NULL) {
		LOG_ERR("There was a problem running the command '%s'", cmd);
		string_list_delete(ol);
		return NULL;
	}

	StringBuilder *sb = string_builder_new();
	
	// Buffer the output
	char buffer[BUFFER_SIZE];
	size_t bytes = 0;
	while ((bytes = fread(buffer, sizeof(char), BUFFER_SIZE, ps_out))) {
		LOG_INFO("Read %ld bytes", bytes);
		for (int i = 0; i < bytes; i++) {
			const char c = buffer[i];
			if (c == '\n') {
				// Append the line to the output list
				char *line = string_builder_clone(sb);
				string_list_append(ol, line);

				// Reset the string builder for the next line
				string_builder_clear(sb);
			} else {
				string_builder_append_length(sb, buffer + i, 1);
			}
		}
	}

	sb = string_builder_delete(sb);
	
	return ol;
}

