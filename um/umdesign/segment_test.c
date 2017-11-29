/*
 *                  segment_test.c
 *
 *      Author: Shucheng Tian and Yirong Tang
 *
 *      This is a unit test for our Segmented Memory for 
 *      our UM.
 *      
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assert.h"
#include "memory.h"
#include "segment.h"
#include "segment_test.h"


static bool OK = 1;

int main(int argc, char *argv[])
{
	(void) argc;
	(void) argv;
	bool clear = true;
	clear = (test_init_free() && test_map_unmap() && test_put_get() &&
	                                                    test_get_command());

	printf("Segmented memory is %sOK!\n", (clear ? "" : "NOT "));
	return(EXIT_SUCCESS);
}

bool test_init_free(void)
{
        Mem memory = mem_init();
        mem_free(&memory);
        OK = (memory == NULL);
        printf("Initialization and Free are %sOK!\n", (OK ? "" : "NOT "));
        return OK;
}

bool test_map_unmap(void)
{
	Mem memory = mem_init();
	for (int i = 0; i < 20; i++) {
		mem_on(&memory, i, i+1);
		/* check if the mapped segment is of correct length */
		/* mem_on in the previous step mapped 
		   the ith element in the memory*/
		OK = (Seg_length(Seq_get(memory,i)) == i+1);
		mem_off(&memory, i);
		OK = (Seq_get(memory,i) == NULL);
	}
	mem_free(&memory);
	printf("Mapping and Unmapping are %sOK!\n", (OK ? "" : "NOT "));
	return OK;
}

bool test_put_get(void)
{
	Mem memory = mem_init();
	for (unsigned i = 0; i < 20; i++) {
		mem_on(&memory, i, i+1);
		/* mem_on in the previous step mapped 
		   the ith element in the memory*/
		/* put value (i+1) at segment i, index i */
        mem_put(&memory, i, i, i + 1);
        /* checking mem_get */
        OK = (mem_get(&memory, i, i) == i + 1);
		mem_off(&memory, i);
	}
	mem_free(&memory);
	printf("Putting and getting values are %sOK!\n", (OK ? "" : "NOT "));
	return OK;
}

bool test_get_command(void)
{
	Mem memory = mem_init();
	/* dummy program */
	int umprog[3] = {0x00001111, 0x11112222, 0x22223333};
	/* 
	 * create a ten-word memory segment at $m[0]
	 * to simulate a ten-instruction um program
	 */
	mem_on(&memory, 0, 3);
	for (unsigned i = 0; i < 3; i++) {
		/* simulate instruction load */
		mem_put(&memory, 0, i, umprog[i]);
	}
	for (unsigned i = 0; i < 3; i++) {
		OK = (get_command(&memory,i) == (uint32_t)umprog[i]);
	}
	mem_off(&memory, 0);
	mem_free(&memory);
	printf("Getting instructions is %sOK!\n", (OK ? "" : "NOT "));
	return OK;
}

