/*
 *                  memory.h
 *
 *      Author: Shucheng Tian and Yirong Tang
 *
 *      This is the interface of the Segmented Memory for our UM
 *      
 */

#ifndef MEMORY_INCLUDED
#define MEMORY_INCLUDED

#include <seq.h>
#include <stdint.h>
#include "uarray.h"

typedef Seq_T Mem;

Mem mem_init();
void mem_free(Mem* mem);
int mem_length(Mem mem);
void mem_put(Mem mem, uint32_t segmentID, uint32_t offset, uint32_t val);
uint32_t mem_get(Mem mem, uint32_t segmentID, uint32_t offset);
uint32_t get_command(Mem mem, uint32_t pcounter);
UArray_T mem_get_seg(Mem mem, uint32_t segmentID);
uint32_t mem_on(Mem mem, uint32_t segmentID, uint32_t length);
void mem_off(Mem mem, uint32_t segmentID);
int loadprog_helper(Mem mem, uint32_t segmentID);

#endif
