/*
 * author     : avinandan sengupta
 * reg no     : 2010CSY7543
 * course     : CSL630
 * assignment : Fibonacci heap
 * file       : fibheap.h
 * purpose    : Fibonacci heap API
 */

#ifndef _fibheap_h_
#define _fibheap_h_

#include "node.h"

/*
 * comparator : pointer to function
 * param1     : lhs 
 * param2     : rhs
 * return     : 0, if lhs == rhs, < 0 if lhs < rhs, > 0 if lhs > rhs
 */
typedef int ( *comparator_t )( heapkey_t lhs, heapkey_t rhs );

/* subtracts delta from key, and updates key with new value */
typedef heapkey_t ( *subtractor_t )( heapkey_t key, heapkey_t delta );

/* pointer to a function that copies an object of generic key type */
typedef void ( *copier_t )( heapkey_t *destination, heapkey_t *source );

/* pointer to a function that prints a key in the heap */
typedef void ( *keyprinter_t )( char* indent, heapkey_t key );

/* handle to Fibonacci heap
 * opaque in nature
 */
typedef struct fibheap *fibheap_t;

/*
 * createheap
 * in      : pointer to a Fibonacci heap handle
 * returns : handle to the newly created heap
 */
fibheap_t createheap( fibheap_t *f );

/* destroyheap
 * in      : Fibonacci heap handle
 */
void destroyheap( fibheap_t f );

/*
 * insert
 * in      : pointer to a Fibonacci heap handle
 * returns : handle to the newly created heap
 */
void insert( fibheap_t f, node_t* node );

/*
 * deletemin
 * in      : pointer to a Fibonacci heap handle
 * returns : handle to the newly created heap
 */
node_t *deletemin( fibheap_t f );

/*
 * decreasekey
 * in      : pointer to a Fibonacci heap handle
 * returns : handle to the newly created heap
 */
void decreasekey( fibheap_t f, node_t *node, heapkey_t delta );

/*
 * createheap
 * in      : pointer to a Fibonacci heap handle
 * returns : handle to the newly created heap
 */
node_t *findmin( fibheap_t f );

/*
 * createheap
 * in      : pointer to a Fibonacci heap handle
 * returns : handle to the newly created heap
 */
void delete( fibheap_t f, node_t *node );

/*
 * nerge
 * in      : pointer to a Fibonacci heap handle
 * returns : handle to the newly created heap
 */
fibheap_t merge( fibheap_t firstheap, fibheap_t secondheap, fibheap_t *outheap );

/* auxilliary function to set and get the contained
 * data kind within the heap
 */
void setkind( fibheap_t f, kind_t kind );

kind_t getkind( fibheap_t f );

void setcomparator( fibheap_t f, comparator_t comparator );

comparator_t getcomparator( fibheap_t f );

void setsubtractor( fibheap_t f, subtractor_t subtractor );

subtractor_t getsubtractor( fibheap_t f );

void setcopier( fibheap_t f, copier_t copier );

copier_t getcopier( fibheap_t f );

void setiota( fibheap_t f, heapkey_t *delta );

heapkey_t *getiota( fibheap_t f );

void setkeyprinter( fibheap_t f, keyprinter_t printer );

keyprinter_t getprinter( fibheap_t f );

void dumpheap( fibheap_t f );

#endif

/* end of file */

