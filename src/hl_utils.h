#ifndef __HL_UTILS_H
#define __HL_UTILS_H

#include "stddef.h"
#include "string_list.h"

const StringList *hl_get_available_versions();

const StringList *hl_get_installed_versions();

void hl_install_version(const char *version);

void hl_rm_version(const char *version);

#endif

