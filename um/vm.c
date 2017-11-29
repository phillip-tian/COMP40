/*
 *                  vm.c
 *
 *      Author: Shucheng Tian and Yirong Tang
 *
 *      This is the implementation of our Virtual Machine Component
 *      that actually manage memory and execution of the program
 *      
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vm.h"
#include "bitpack.h"
#include "instruction.h"

/* register */
static uint32_t r[8] = {0,0,0,0,0,0,0,0};
/* program counter */
static int program_counter = 0;

/*
 * name: run
 * parameter: UArray_T
 * returns: void
 * does: run the program
 */

static inline uint64_t getr(uint64_t word, unsigned width, unsigned lsb)
{
        return (word << (64 - lsb - width)) >> (64 - width);
}

static inline uint32_t mem_get_command(Mem memory, uint32_t segmentID, uint32_t offset)
{
        UArray_T curr = Seq_get(memory, segmentID);
        return *((uint32_t *)UArray_at(Seq_get(memory, segmentID), offset));
}

void run(UArray_T program)
{
        /* Initialize UM */
        Mem memory = mem_init();
        Stack_T unmapped = Stack_new();
        int program_length = UArray_length(program);
        uint32_t a, b, c;
        Seq_addhi(memory, program);
        
        while (program_counter < program_length) {
                uint32_t command = mem_get_command(memory, 0, program_counter);
                uint32_t opcode = getr(command, 4, 28);
        	switch (opcode) {
                        case 0:
                                a = getr(command, 3, 6);
                                b = getr(command, 3, 3);
                                c = getr(command, 3, 0);

                                cmove(a, b, c, r);
                                break;
                        case 1:
                                a = getr(command, 3, 6);
                                b = getr(command, 3, 3);
                                c = getr(command, 3, 0);

                                sload(a, b, c, r, memory);
                                break;
                        case 2: 
                                a = getr(command, 3, 6);
                                b = getr(command, 3, 3);
                                c = getr(command, 3, 0);

                                sstore(a, b, c, r, memory);
                                break;
                        case 3:
                                a = getr(command, 3, 6);
                                b = getr(command, 3, 3);
                                c = getr(command, 3, 0);

                                add(a, b, c, r);
                                break;
                        case 4:
                                a = getr(command, 3, 6);
                                b = getr(command, 3, 3);
                                c = getr(command, 3, 0);

                                mul(a, b, c, r);
                                break;
                        case 5:
                                a = getr(command, 3, 6);
                                b = getr(command, 3, 3);
                                c = getr(command, 3, 0);

                                divid(a, b, c, r);
                                break;
                        case 6:
                                a = getr(command, 3, 6);
                                b = getr(command, 3, 3);
                                c = getr(command, 3, 0);

                                nand(a, b, c, r);
                                break;
                        case 7:
                                halt(memory, unmapped);
                                break;
                        case 8:
                                b = getr(command, 3, 3);
                                c = getr(command, 3, 0);

                                mapSegment(b, c, r, memory, unmapped);
                                break;
                        case 9:
                                c = getr(command, 3, 0);

                                unmapSegment(c, r, memory, unmapped);
                                break;
                        case 10:
                                c = getr(command, 3, 0);

                                output(c, r);
                                break;
                        case 11:
                                c = getr(command, 3, 0);

                                input(c, r);
                                break;
                        case 12:
                                b = getr(command,3,3);
                                c = getr(command,3,0);

                                loadprog(b, c, r, memory, &program_counter, 
					 &program_length);

                                break;
                        case 13:
                                a = getr(command,3,25);
                                uint32_t val = getr(command,25,0);

                                loadval(a, val, r);
                                break;
        	}
                program_counter++;
        }
}
