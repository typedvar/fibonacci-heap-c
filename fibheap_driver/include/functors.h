/*
 * author     : avinandan sengupta
 * file       : functors.h
 * purpose    : various callback functor declarations
 */
#ifndef _functors_h_
#define _functors_h_

#include "fibheap.h"

void print_key( char* indent, heapkey_t lhs );

int compare_records( heapkey_t lhs, heapkey_t rhs );

int compare_strings_ht( htkey_t lhs, htkey_t rhs );

int compare_int_ht( htkey_t lhs, htkey_t rhs );

heapkey_t subtract_key( heapkey_t key, heapkey_t delta );

void copy_key( heapkey_t *destination, heapkey_t *source );

htkey_t copy_key_ht( htkey_t source, memop_t mop );

unsigned int intkeyhasher( htkey_t key );

unsigned int fltkeyhasher( htkey_t key );

unsigned int strkeyhasher( htkey_t key );

#endif

/* end of file */
