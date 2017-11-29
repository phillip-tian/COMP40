/*
 *                  memory.c
 *
 *      Author: Shucheng Tian and Yirong Tang
 *
 *      This .c file contains implementation of the segmented memory 
 *      of our um.
 */


#include "memory.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "assert.h"


/* initialize the segmented memory */
Mem mem_init()
{
	return Seq_new(10); 
}

/* free segmented memory */ 
void mem_free(Mem* memory)
{
	Seq_free(memory);
}

/* return the length of the segmented memory */ 
int mem_length(Mem memory)
{
	return Seq_length(memory);
}

/* put val into the memory at [segmentID][offset] */
void mem_put(Mem memory, uint32_t segmentID, uint32_t offset, uint32_t val)
{
        UArray_T curr = Seq_get(memory, segmentID);
        *((uint32_t *)UArray_at(curr, offset)) = val;
}

/* get the value stored in memory at [segmentID][offset] */
uint32_t mem_get(Mem memory, uint32_t segmentID, uint32_t offset)
{
	UArray_T curr = Seq_get(memory, segmentID);
	return *((uint32_t *)UArray_at(curr, offset));
}

/* get the instruction at [pcounter] in $m[0] */
uint32_t get_command(Mem memory, uint32_t pcounter)
{
	UArray_T curr = Seq_get(memory, 0);
        return *((uint32_t *)UArray_at(curr, pcounter));
}

/* get the segment $m[segmentID] */
UArray_T mem_get_seg(Mem memory, uint32_t segmentID)
{
        return Seq_get(memory, segmentID);
}

/* helper function for Map Segment */
uint32_t mem_on(Mem memory, uint32_t segmentID, uint32_t length)
{
        if((int)segmentID >= mem_length(memory)) {
                /* need to map new segment(Seq_addhi) */
                UArray_T new = UArray_new(length, sizeof(uint32_t));
                assert(new);
                int len = UArray_length(new);

                for (int i = 0; i < len; i++) {
                	*((uint32_t *)UArray_at(new, i)) = 0;
                }
                Seq_addhi(memory, new);
                int seq_len = Seq_length(memory);
                return (seq_len - 1);
        } else {
        	UArray_T new = UArray_new(length, sizeof(uint32_t));
                assert(new);
                int len = UArray_length(new);
        	for (int i = 0; i < len; i++) {
                        *((uint32_t *)UArray_at(new, i)) = 0;
                }
                Seq_put(memory, segmentID, new);
                return segmentID;
        }
}

/* helper function for Unmap Segment */
void mem_off(Mem mem, uint32_t segmentID)
{
	UArray_T temp = Seq_get(mem, segmentID);
	UArray_free(&temp);
	Seq_put(mem, segmentID, NULL);
}

/* helper function for load program */
int loadprog_helper(Mem mem, uint32_t segmentID)
{
        UArray_T temp_program = Seq_get(mem, segmentID);
        uint32_t program_length = UArray_length(temp_program);
        /* duplicate program */
        UArray_T new_program = UArray_copy(temp_program, program_length);
        UArray_T old_program = Seq_get(mem, 0);
        UArray_free(&old_program);
	Seq_put(mem, 0, new_program);
	return program_length; /* for updating the program length */
}
