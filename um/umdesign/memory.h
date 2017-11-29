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

typedef Seq_T Mem;

/* initialize the segmented memory */
Mem mem_init();

/* free segmented memory */ 
void mem_free(Mem* mem);

/* returns the length of the segmented memory */ 
int mem_length(Mem mem);

/* put val into the memory at [index][offset] */
void mem_put(Mem* mem, uint32_t index, uint32_t offset, uint32_t val);

/* get the value stored in memory at [index][offset] */
uint32_t mem_get(Mem* mem, uint32_t index, uint32_t offset);

/* get the instruction at [pcounter] in $m[0] */
uint32_t get_command(Mem* mem, uint32_t pcounter);

/* helper function for Map Segment */
/* return segment id for R[b] */
uint32_t mem_on(Mem* mem, uint32_t index, uint32_t length);

/* helper function for Unmap Segment */
/* return (unmapped) segment id for stack */
uint32_t mem_off(Mem* mem, uint32_t index);



#endif