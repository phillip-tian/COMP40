/*
 *                  segment_test.h
 *
 *      Author: Shucheng Tian and Yirong Tang
 *
 *      This is the interface of the unit test for our Segmented  
 *      Memory for our UM.
 *      
 */

#ifndef SEGMENT_TEST_INCLUDED
#define SEGMENT_TEST_INCLUDED

bool test_init_free(void);
bool test_map_unmap(void);
bool test_put_get(void);
bool test_get_command(void);

#endif