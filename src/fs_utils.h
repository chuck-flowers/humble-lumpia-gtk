#ifndef __FS_UTILS_H
#define __FS_UTILS_H

void initialize_fs_utils();

/**
 * Gets a file that has been installed with the humble-lumpia installation.
 */
const char *get_installed_file(const char *rel_path);

const int file_exists(const char *path);

#endif

