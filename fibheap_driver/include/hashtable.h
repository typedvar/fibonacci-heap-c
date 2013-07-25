/*
 * author     : avinandan sengupta
 * reg no     : 2010CSY7543
 * course     : CSL630
 * assignment : Fibonacci heap
 * file       : hashtable.h
 * purpose    : hash table API and interfaces
 */

#ifndef _hashtbl_h_
#define _hashtbl_h_

#include "node.h"

/* opaque pointer to the hash table
 *
 */
typedef struct hashtable *hashtable_t;

/* generic value type
 */
typedef void *value_t;

/* generic key type
 */
typedef void *htkey_t;

typedef enum memop
{
    MOP_ALLOC,
    MOP_DELETE
} memop_t ;

typedef unsigned int ( *hashfunc_t )( htkey_t key );

/*
 * param1     : lhs
 * param2     : rhs
 * return     : 0, if lhs == rhs, < 0 if lhs < rhs, > 0 if lhs > rhs
 */
typedef int ( *htkeycomparator_t )( htkey_t lhs, htkey_t rhs );

typedef htkey_t ( *htkeyallocator_t )( htkey_t source, memop_t mop );

hashtable_t createht( size_t numelems );

void deleteht( hashtable_t h );

void installkv( hashtable_t h, htkey_t key, value_t val );

value_t removekv( hashtable_t h, htkey_t key );

value_t lookupkv( hashtable_t h, htkey_t key );

void sethashfunc( hashtable_t h, hashfunc_t hashfunc );

hashfunc_t gethashfunc( hashtable_t h );

void sethtkeycomparator( hashtable_t h, htkeycomparator_t keycomp );

htkeycomparator_t gethtkeycomparator( hashtable_t h );

void sethtkeyallocator( hashtable_t h, htkeyallocator_t keyallocator );

htkeyallocator_t gethtkeyallocator( hashtable_t ht );

int isemptyht( hashtable_t h );

size_t getsizeht( hashtable_t h );

#endif 
/* end of file */

