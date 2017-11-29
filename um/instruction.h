/*
 *                  instructions.h
 *
 *      Author: Shucheng Tian and Yirong Tang
 *
 *      This is the header file for 14 um instructions.
 *      
 */


#ifndef INSTRUCTION_INCLUDED
#define INSTRUCTION_INCLUDED

#include <stdint.h>

#include "stack.h"
#include "memory.h"

void cmove(uint32_t a, uint32_t b, uint32_t c, uint32_t *r);
void sload(uint32_t a, uint32_t b, uint32_t c, uint32_t *r, Mem memory);
void sstore(uint32_t a, uint32_t b, uint32_t c, uint32_t *r, Mem memory);
void add(uint32_t a, uint32_t b, uint32_t c, uint32_t *r);
void mul(uint32_t a, uint32_t b, uint32_t c, uint32_t *r);
void divid(uint32_t a, uint32_t b, uint32_t c, uint32_t *r);
void nand(uint32_t a, uint32_t b, uint32_t c, uint32_t *r);
void halt(Mem mem, Stack_T unmapped);
void mapSegment(uint32_t b, uint32_t c, uint32_t *r, Mem memory, Stack_T unmapped);
void unmapSegment(uint32_t c, uint32_t *r, Mem memory, Stack_T unmapped);
void output(uint32_t c, uint32_t *r);
void input(uint32_t c, uint32_t *r);
void loadprog(uint32_t b, uint32_t c, uint32_t* r, Mem memory, int* ctr, int* proglength);
void loadval(uint32_t a, uint32_t val, uint32_t* r);


#endif
