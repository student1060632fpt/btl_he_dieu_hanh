// Functions used by the loader which load the program from disk to memory
// các hàm được dùng bởi loader mà load program từ disk tới memory

#ifndef LOADER_H
#define LOADER_H

#include "common.h"

struct pcb_t * load(const char * path);

#endif

