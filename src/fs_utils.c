#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "fs_utils.h"
#include "logging.h"
#include "string_builder.h"

static const char* SYS_INSTALL_PREFIX = "/usr";
static const char* LOCAL_SYS_INSTALL_PREFIX = "/usr/local";
static const char* USER_INSTALL_PREFIX = NULL;

void initialize_fs_utils() {
	LOG_TRACE("initialize_fs_utils");

	if (USER_INSTALL_PREFIX == NULL) {
		const char *home_dir = getenv("HOME");

		// Builds the path
		StringBuilder *sb = string_builder_new();
		string_builder_append(sb, home_dir);
		string_builder_append(sb, "/.local");

		USER_INSTALL_PREFIX = string_builder_delete_and_take(sb);
	}
}

const char *get_installed_file(const char *rel_path) {
	LOG_TRACE("get_installed_file(%s)", rel_path);

	// Check the user prefix
	StringBuilder *sb = string_builder_new();
	string_builder_append(sb, USER_INSTALL_PREFIX);
	string_builder_append(sb, rel_path);
	if (file_exists(sb->buffer)) {
		return string_builder_delete_and_take(sb);
	}

	// Check the local sys prefix
	string_builder_clear(sb);
	string_builder_append(sb, LOCAL_SYS_INSTALL_PREFIX);
	string_builder_append(sb, rel_path);
	if (file_exists(sb->buffer)) {
		return string_builder_delete_and_take(sb);
	}

	// Check the sys prefix
	string_builder_clear(sb);
	string_builder_append(sb, SYS_INSTALL_PREFIX);
	string_builder_append(sb, rel_path);
	if (file_exists(sb->buffer)) {
		return string_builder_delete_and_take(sb);
	}

	// No such file was found
	string_builder_delete(sb);
	return NULL;
}

const int file_exists(const char *path) {
	LOG_TRACE("file_exists(\"%s\")", path);

	FILE *file = fopen(path, "r");
	if (file == NULL) {
		fclose(file);
		return 0;
	} else {
		fclose(file);
		return 1;
	}
}

