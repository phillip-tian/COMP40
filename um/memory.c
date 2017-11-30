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
        //UArray_T curr = Seq_get(memory, segmentID);
        struct seg *curr = Seq_get(memory, segmentID);
        //*((uint32_t *)UArray_at(curr, offset)) = val;
        curr->segment[offset] = val;
}

/* get the value stored in memory at [segmentID][offset] */
uint32_t mem_get(Mem memory, uint32_t segmentID, uint32_t offset)
{
	//UArray_T curr = Seq_get(memory, segmentID);
        struct seg *curr = Seq_get(memory, segmentID);
	//return *((uint32_t *)UArray_at(curr, offset));
        return curr->segment[offset];
}

/* get the segment $m[segmentID] */
struct seg* mem_get_seg(Mem memory, uint32_t segmentID)
{
        return ((struct seg*)Seq_get(memory, segmentID));
}

/* helper function for Map Segment */
uint32_t mem_on(Mem memory, uint32_t segmentID, uint32_t length)
{
        if((int)segmentID >= mem_length(memory)) {
                // printf("here\n");
                /* need to map new segment(Seq_addhi) */
                //UArray_T new = UArray_new(length, sizeof(uint32_t));
                struct seg *newseg = NULL;
                newseg = malloc(sizeof(struct seg));
                newseg->segment = malloc(length * sizeof(uint32_t));
                newseg->segment_len = length;
                // printf("newseg length = %d\n",newseg->segment_len);
                //int len = UArray_length(new);

                for (unsigned i = 0; i < length; i++) {
                	newseg->segment[i] = 0;
                }
                Seq_addhi(memory, newseg);
                int seq_len = Seq_length(memory);
                return (seq_len - 1);
        } else {
        	struct seg *newseg = NULL;
                newseg = malloc(sizeof(struct seg));
                newseg->segment = malloc(length * sizeof(uint32_t));
                newseg->segment_len = length;
                //int len = UArray_length(new);

                for (unsigned i = 0; i < length; i++) {
                        newseg->segment[i] = 0;
                }
                Seq_put(memory, segmentID, newseg);
                return segmentID;
        }
}

/* helper function for Unmap Segment */
void mem_off(Mem mem, uint32_t segmentID)
{
	struct seg *temp = Seq_get(mem, segmentID);
	//UArray_free(&temp);
        // printf("temp length = %d\n",temp->segment_len);
        free(temp->segment);
	Seq_put(mem, segmentID, NULL);
}

/* helper function for load program */
int loadprog_helper(Mem mem, uint32_t segmentID)
{
        struct seg *temp_program = Seq_get(mem, segmentID);
        uint32_t program_length = temp_program->segment_len;
        /* duplicate program */
        //UArray_T new_program = UArray_copy(temp_program, program_length);
        struct seg *new_program = NULL;
        new_program = malloc(sizeof(struct seg));
        new_program->segment = malloc(program_length * sizeof(uint32_t));
        new_program->segment_len = program_length;
        for (unsigned i = 0; i < program_length; i++) {
                new_program->segment[i] = temp_program->segment[i];
        }

        //UArray_T old_program = Seq_get(mem, 0);
        //UArray_free(&old_program);
        
        struct seg *destroy_program = Seq_get(mem, 0);
        free(destroy_program->segment);

	Seq_put(mem, 0, new_program);
	return program_length; /* for updating the program length */
}
