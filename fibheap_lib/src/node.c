/*
 * author     : avinandan sengupta
 * file       : node.c
 * purpose    : implementation of node functionality
 */

#include <assert.h>
#include <stdlib.h>
#include <memory.h>

#include "node.h"

node_t *createnode( heapkey_t key )
{
    node_t *ret = NULL;

    ret = ( node_t * )malloc( sizeof( node_t ) );

    ret->parent = NULL;
    ret->firstchild = NULL;
    ret->leftsibling = ret;
    ret->rightsibling = ret;
    ret->degree = 0;
    ret->cutcount = 0;
    memcpy( &ret->key, &key, sizeof( heapkey_t ) );
    return ret;
}

void destroynode( node_t *node )
{
	assert( node );
    if( node != NULL )
    {
        //free( node );
    }
}

void splicenodes( node_t *node1, node_t *node2 )
{   
    node_t *old_node1_right = NULL;
	assert( node1 );
	assert( node2 );

    old_node1_right = node1->rightsibling;

    node1->rightsibling = node2->rightsibling;
    node2->rightsibling->leftsibling = node1;

    node2->rightsibling = old_node1_right;
    old_node1_right->leftsibling = node2;
}

node_t *removenode( node_t *node )
{
    node_t *retval = NULL;

	assert( node );

	if( node != node->rightsibling )
	{
        retval = node->rightsibling;
		node->leftsibling->rightsibling = node->rightsibling;
		node->rightsibling->leftsibling = node->leftsibling;

		node->rightsibling = node->leftsibling = node;
	}

    return retval;
}

node_t *adopt( node_t *parent, node_t *child )
{
	node_t *old_right = NULL;
	assert( parent );
	assert( child );

	/* add child to childlist */
	if( parent->firstchild )
	{
		old_right = parent->firstchild->rightsibling;
		parent->firstchild->rightsibling = child;
		child->leftsibling = parent->firstchild;
		child->rightsibling = old_right;
		old_right->leftsibling = child;
	}
	else
	{
		parent->firstchild = child;
	}

	/* link up to the parent */
	child->parent = parent;

	/* increment child count */
	++parent->degree;
	return parent;
}

/* end of file */

