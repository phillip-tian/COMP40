/*
 *                  um.c
 *
 *      Author: Shucheng Tian and Yirong Tang
 *
 *      This is the driver of our Universal Machine Program
 *      
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "uarray.h"
#include "load.h"
#include "vm.h"

int main(int argc, char *argv[]) {
        struct seg *instruction = load(argc, argv);
        run(instruction);
        return (EXIT_SUCCESS);
}