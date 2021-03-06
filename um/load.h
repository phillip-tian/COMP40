/*
 *                  load.h
 *
 *      Author: Shucheng Tian and Yirong Tang
 *
 *      This is a header file for load component
 *      of our Universal Machine Program
 *      
 */

#ifndef LOAD_INCLUDED
#define LOAD_INCLUDED

#include <stdint.h>

#include "seg.h"

struct seg *load(int argc, char* argv[]);

#endif
