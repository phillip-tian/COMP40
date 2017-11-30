/*
 *                  vm.h
 *
 *      Author: Shucheng Tian and Yirong Tang
 *
 *      This is the interface of our Virtual Machine Component
 *      that actually manage memory and execution of the program
 *      
 */

#ifndef VM_INCLUDED
#define VM_INCLUDED

#include "load.h"

void run(struct seg *program);

#endif