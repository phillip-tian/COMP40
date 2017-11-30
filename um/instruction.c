/*
 *                  instructions.c
 *
 *      Author: Shucheng Tian and Yirong Tang
 *
 *      This .c file contains implementation of 14 um instructions.
 *      
 */

#include "instruction.h"
#include "assert.h"
#include <stdio.h>
#include <stdlib.h>

/* 
 * 0: contional move instruction 
 * if $r[C] != 0 then $r[A] := $r[B]
 */
void cmove(uint32_t a, uint32_t b, uint32_t c, uint32_t *r)
{
        if (r[c] != 0) {
                r[a] = r[b];
        }
}

/*
 * 1: Segmented Load 
 * $r[A] := $m[$r[B]][$r[C]]
 */
void sload(uint32_t a, uint32_t b, uint32_t c, uint32_t *r, Mem memory)
{
        r[a] = mem_get(memory, r[b], r[c]);
}

/*
 * 2: Segmented Store 
 * $m[$r[A]][$r[B]] := $r[C]
 */
void sstore(uint32_t a, uint32_t b, uint32_t c, uint32_t *r, Mem memory)
{
        mem_put(memory, r[a], r[b], r[c]);
}

/*
 * 3: add instruction
 * $r[A] := ($r[B] + $r[C]) mod 255
 */
void add(uint32_t a, uint32_t b, uint32_t c, uint32_t *r)
{
        r[a] = (r[b] + r[c]); //%4294967296
}

/*
 * 4: multiplication instruction 
 * $r[A] := ($r[B] × $r[C]) mod 255
 */
void mul(uint32_t a, uint32_t b, uint32_t c, uint32_t *r)
{
        r[a] = (r[b] * r[c]); //%4294967296
}

/*
 * 5: division instruction 
 * $r[A] := ⌊$r[B] ÷ $r[C]⌋
 */
void divid(uint32_t a, uint32_t b, uint32_t c, uint32_t *r)
{
        r[a] = (r[b] / r[c]); //%4294967296
}

/* 
 * 6: Bitwise NAND instruction 
 * $r[A] := ¬($r[B] ∧ $r[C])
 */
void nand(uint32_t a, uint32_t b, uint32_t c, uint32_t *r)
{
        r[a] = ~(r[b] & r[c]);
}

/* 
 * 7: halt instruction 
 * Computation stops.
 */
void halt(Mem memory, Stack_T unmapped)
{
        /* 
         * program count = program_length, moving the program count to the last
         * instruction
         */
        //printf("%d\n", mem_length(memory));

        //struct seg* temp = mem_get_seg(memory,1500);
        //printf("temp length = %d\n", temp -> segment_len);
        for(int i = 0; i < mem_length(memory); i++){
                if (mem_get_seg(memory, i) != NULL) {
                         mem_off(memory, i);
                }
        //printf("%d\n",i);
        }
        Stack_free(&unmapped);
        mem_free(&memory);
        exit(EXIT_SUCCESS);
}

/*
 * 8: Map Segment
 * A new segment is created with a number of words equal to the value 
 * in $r[C]. Each word in the new segment is initialized to 0. A bit 
 * pattern that is not all zeroes and that does not identify any currently 
 * mapped segment is placed in r[B]. The new segment is mapped as $m[$r[B]]
 */
void mapSegment(uint32_t b, uint32_t c, uint32_t *r, Mem memory, 
		Stack_T unmapped)
{
        if (Stack_empty(unmapped) == 1) {
                r[b] = mem_on(memory, mem_length(memory), r[c]);
        } else {
                uint32_t id = (uint32_t)(uintptr_t)Stack_pop(unmapped);
                r[b] = mem_on(memory, id, r[c]);
        }
}

/*
 * 9: Unmap Segment
 * The segment $m[$r[C]] is unmapped. Future Map Segment instructions may 
 * reuse the identifier $r[C].
 */
void unmapSegment(uint32_t c, uint32_t *r, Mem memory, Stack_T unmapped)
{
        mem_off(memory, r[c]);
        Stack_push(unmapped, (void*)(uintptr_t)r[c]);
}

/*
 * 10: output instruction 
 * The value in $r[C] is displayed on the I/O device immediately. Only 
 * values from 0 to 255 are allowed.
 */
void output(uint32_t c, uint32_t *r)
{
        putchar(r[c]);
}

/* 
 * 11: input instruction 
 * The universal machine waits for input on the I/O device. When input 
 * arrives, $r[C] is loaded with the input, which must be a value from 0 
 * to 255. If the end of input has been signaled, then $r[C] is loaded 
 * with a full 32-bit word in which every bit is 1.
 */
void input(uint32_t c, uint32_t *r)
{
        uint32_t input = getchar();
        if (input == (uint32_t)EOF) {
               input = ~0; 
        }
	assert(input <= 255 || input == (uint32_t)EOF);
        r[c] = input;
}
/*
 * 12: load program instruction
 * Segment $m[$r[B]] is duplicated, and the duplicate replaces $m[0], 
 * which is abandoned. The program counter is set to point to $m[0][$r[C]] 
 */
void loadprog(uint32_t b, uint32_t c, uint32_t* r, Mem memory, int* ctr, 
	      int* proglength)
{
        if (r[b] == 0) {
                *ctr = r[c] - 1; /*to offset counter++ after switch statement*/
        } else {
                int new_prog_len = loadprog_helper(memory, r[b]);
		        *proglength = new_prog_len;
                *ctr = r[c] - 1;
        }
}

/*
 * 13: load value instruction
 * Load val into $r[A] 
 */
void loadval(uint32_t a, uint32_t val, uint32_t* r)
{
        r[a] = val;
}
