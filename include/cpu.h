// Define functions used to implement the virtual CPU
//Xác định các chức năng được sử dụng để triển khai CPU ảo

#ifndef CPU_H
#define CPU_H

#include "common.h"

/* Execute an instruction of a process. Return 0
 * if the instruction is executed successfully.
 * Otherwise, return 1. */
int run(struct pcb_t * proc);

#endif

