/*
 * author     : avinandan sengupta
 * reg no     : 2010CSY7543
 * course     : CSL630
 * assignment : Fibonacci heap
 * file       : fibheap_int.h
 * purpose    : Fibonacci heap internal data structures
 */

#ifndef _fibheap_int_h_
#define _fibheap_int_h_

typedef struct fibheap
{
    node_t       *min;        /* pointer to the tree root with minimum key */
    kind_t        kind;       /* data type of the node values              */
    comparator_t  comparator; /* function pointer to the comparator        */
    subtractor_t  subtractor; /* function pointer to the subtractor        */
    keyprinter_t  keyprinter; /* function pointer to the key printer       */
    copier_t      copier;     /* function pointer to the key copier        */
    heapkey_t    *iota;       /* iota that can make a key the minimum      */
    unsigned int  numnodes;   /* number of nodes in the heap               */
} fibheap_internal_t;

typedef enum loglevel
{
	LGL_INFO,
	LGL_WARN,
	LGL_ERRO,
	LGL_MAX
} loglevel_t;

#endif

/* end of file */

