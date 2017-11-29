/*
 *                  segment.h
 *
 *      Author: Shucheng Tian and Yirong Tang
 *
 *      This is the interface of the sub-component(segment) of the Segmented 
 *      Memory for our UM
 *      
 */

#ifndef SEGMENT_INCLUDED
#define SEGMENT_INCLUDED


#include <uarray.h>
#include <stdint.h>

typedef UArray_T Seg;
/* initialize a segment with given length */
Seg Seg_new(int length);

/* free segment */ 
void Seg_free(Seg* arr);

/* put val into a given segment at index = offset */
void Seg_put(Seg arr, uint32_t offset, uint32_t val);

/* get the value stored in segment at index = offset */
uint32_t Seg_get(Seg arr, uint32_t offset);

/* return the length of segment arr */ 
int Seg_length(Seg arr);

#endif