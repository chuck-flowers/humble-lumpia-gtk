#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logging.h"
#include "hl_utils.h"
#include "process_utils.h"
#include "string_builder.h"
#include "string_list.h"

const StringList *hl_get_available_versions() { 
	LOG_TRACE("hl_get_available_versions");

	StringList *sl = runProcess("humble-lumpia ls");
	if (sl == NULL) {
		LOG_ERR("Failed to run humble-lumpia to get the versions");
	}

	return sl;
}

const StringList *hl_get_installed_versions() { 
	LOG_TRACE("hl_get_installed_versions");

	StringList *sl = runProcess("humble-lumpia ls --installed");
	if (sl == NULL) {
		LOG_ERR("Failed to run humble-lumpia to get the installed versions");
	}

	return sl;
}

void hl_install_version(const char *version) { 
	LOG_TRACE("hl_install_version");

	const char *cmd_prefix = "humble-lumpia install ";
	const size_t cmd_prefix_length = strlen(cmd_prefix);
	const size_t version_length = strlen(version);

	// Creates the command string
	char cmd_buffer[cmd_prefix_length + version_length + 1];
	sprintf(cmd_buffer, "%s%s", cmd_prefix, version);

	// Run the command
	StringList *sl = runProcess(cmd_buffer);
	string_list_delete(sl);
}

void hl_rm_version(const char *version) { 
	LOG_TRACE("hl_rm_version");

	const char *cmd_prefix = "humble-lumpia rm ";
	const size_t cmd_prefix_length = strlen(cmd_prefix);
	const size_t version_length = strlen(version);

	// Creates the command string
	char cmd_buffer[cmd_prefix_length + version_length + 1];
	sprintf(cmd_buffer, "%s%s", cmd_prefix, version);

	// Run the command
	StringList *sl = runProcess(cmd_buffer);
	string_list_delete(sl);
}

