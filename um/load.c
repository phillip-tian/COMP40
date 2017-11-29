/*
 *                  load.c
 *
 *      Author: Shucheng Tian and Yirong Tang
 *
 *      This is a the implementation for load component
 *      of our Universal Machine Program
 *      
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "load.h"
#include "bitpack.h"

#include <uarray.h>
#include <sys/types.h>
#include <sys/stat.h>

const int WORD_LENGTH = 4;

/* 
 * name: load
 * parameter: int, char*
 * return: int*
 * Does: Reads the binary from .um file passed in by UM component and convert 
 *       the binary to 32-bit word using Bitpack. Ensures the content of the 
 *       given .um is properly formatted
 */
UArray_T load(int argc, char* argv[])
{
        if (argc != 2) {
                fprintf(stderr, "Usage: ./um [filename]\n");
                exit(EXIT_FAILURE);
        }

        struct stat umfile;
        stat(argv[1], &umfile);
        int inst_length = umfile.st_size / WORD_LENGTH;
        UArray_T instructions = UArray_new(inst_length, sizeof(uint32_t));

        FILE* input = fopen(argv[1], "rb");

        if (input == NULL) {
                fprintf(stderr, "Error opening file.\n");
                exit(EXIT_FAILURE);
        }

        uint32_t command = 0;
        for (int i = 0; i < inst_length; i++) {
                for (unsigned k = 24; (int)k >= 0; k -= 8){
                        int curr = getc(input);
                        if (curr == EOF) { 
                                fprintf(stderr,"Not enough code word.\n");
                                exit(EXIT_FAILURE);
                        }       
                        command = Bitpack_newu(command, 8, k, curr);
                }
                *((uint32_t *)UArray_at(instructions, i)) = command;
        }
        fclose(input);
        return instructions;
}

