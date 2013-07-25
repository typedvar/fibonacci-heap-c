/*
 * author     : avinandan sengupta
 * reg no     : 2010CSY7543
 * course     : CSL630
 * assignment : Fibonacci heap
 * file       : node.h
 * purpose    : defines the type node_t and
 *              operations on it
 */

#ifndef _node_h_
#define _node_h_

#include <stdlib.h>

/* enum for the data kinds
 * supported that can be contained
 * in a node of the Fibonacci heap
 */
typedef enum kind
{
    KIND_UNKNOWNN = -1,
    KIND_INT,
    KIND_FLOAT,
    KIND_GENERIC,
    MAX_KINDS
} kind_t;

typedef union key
{
    int   intdata;        /* integer data */
    float realdata;       /* real data    */
    void* genericdata;    /* generic data */
} heapkey_t;

/* Forward declaration for the node
 * type
 */
typedef struct node node_t;

struct node
{
    /* structural data */
    node_t *parent;       /* pointer to the parent node   */
    node_t *firstchild;   /* pointer to the first child   */
    node_t *leftsibling;  /* pointer to the left sibling  */
    node_t *rightsibling; /* pointer to the right sibling */
    size_t  degree;       /* number of children           */
    char    cutcount;     /* number of children removed   */

    /* storage data */
    heapkey_t  key;           /* holds the actual data        */
};

/* operations on nodes */

node_t *createnode( heapkey_t data );

void destroynode( node_t *node );

/* combines two lists into one */
void splicenodes( node_t *node1, node_t *node2 );

/*
 * remove a node from a doubly-circular linked list
 * returns the node to the right of the node being
 * deleter
 */
node_t *removenode( node_t *node );

/*
 * make node the child of parent
 * returns the parent
 */
node_t *adopt( node_t *parent, node_t *node );

#endif

/* end of file */

