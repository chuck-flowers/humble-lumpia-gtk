#ifndef __PROCESS_UTILS_H
#define __PROCESS_UTILS_H

#include "string_list.h"
#include <stddef.h>

StringList *runProcess(const char *cmd);

#endif

