/*
 * author     : avinandan sengupta
 * file       : fibheap.c
 * purpose    : Fibonacci heap implementation core
 */

#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>

#include "fibheap.h"
#include "fibheap_int.h"
#include "fibdefines.h"

#define _FIB_SHOW_OPS_

void setkind( fibheap_t f, kind_t kind )
{
    assert( f );
    f->kind = kind;
}

kind_t getkind( fibheap_t f )
{
    assert( f );
    return f->kind;
}

void setcomparator( fibheap_t f, comparator_t comparator )
{
    assert( f );
    f->comparator = comparator;
}

comparator_t getcomparator( fibheap_t f )
{
    assert( f );
    return f->comparator;
}

void setcopier( fibheap_t f, copier_t copier )
{
    assert( f );
    f->copier = copier;
}

copier_t getcopier( fibheap_t f )
{
    assert( f );
    return f->copier;
}

void setiota( fibheap_t f, heapkey_t *iota )
{
    assert( f );
    f->iota = iota;
}

heapkey_t *getiota( fibheap_t f )
{
    assert( f );
    return f->iota;
}

void setkeyprinter( fibheap_t f, keyprinter_t printer )
{
	assert( f );
	f->keyprinter = printer;
}

keyprinter_t getprinter( fibheap_t f )
{
	assert( f );
	return f->keyprinter;
}

void setsubtractor( fibheap_t f, subtractor_t subtractor )
{
    assert( f );
    f->subtractor = subtractor;
}

subtractor_t getsubtractor( fibheap_t f )
{
    assert( f );
    return f->subtractor;
}

void printkey( fibheap_t f, node_t *node, char* indent )
{
	if( KIND_GENERIC == f->kind && f->keyprinter )
	{
		( *f->keyprinter )( indent, node->key );
	}
	else if( KIND_INT == f->kind )
	{
		printf( "%s %d", indent, node->key.intdata );
	}
	else if( KIND_FLOAT == f->kind )
	{
		printf( "%s %0.2f ", indent, node->key.realdata );
	}
}

fibheap_t createheap( fibheap_t *f )
{
    fibheap_t heap = NULL;
    *f = ( fibheap_t )malloc( sizeof( fibheap_internal_t ) );
    heap = *f;
    memset( heap, 0x0, sizeof( fibheap_internal_t ) );
    heap->min = NULL;
    heap->kind = KIND_INT;
    heap->numnodes = 0;
    heap->comparator = NULL;
    heap->subtractor = NULL;
    heap->copier = NULL;
    heap->keyprinter = NULL;
    heap->iota = NULL;
    return heap;
}

int islessthan( fibheap_t f,
                node_t *lhs, 
                node_t *rhs )
{
    int ret = 0;

    assert( lhs );
	assert( rhs );

    switch( f->kind )
    {
        case KIND_INT:
            ret = ( lhs->key.intdata < rhs->key.intdata ); 
            break;
        case KIND_FLOAT:
            ret = ( lhs->key.realdata < rhs->key.realdata );
            break;
        case KIND_GENERIC:
            assert( f->comparator );
            ret = ( ( *f->comparator )( lhs->key, rhs->key ) < 0 ) ? 1 : 0;
            break;
        default:
            assert( 0 );
    }
    return ret;
}

/* perform consolidation of all nodes and childs */
void consolidate( fibheap_t f )
{
	size_t max_degree = 0;
	size_t node_degree = 0;
	size_t idx = 0;
	int num_reinserted = 0;
	size_t num_nodes = 0;

	node_t **node_table = NULL;
	node_t *node = NULL;
	node_t *temp = NULL;
	node_t *root = NULL;
	node_t *nextnode = NULL;
	root = f->min;

	if( !root )
	{
		return;
	}

	num_nodes = f->numnodes;
	node_table = ( node_t **)calloc( num_nodes, sizeof( node_t* ) );

	do
	{
		nextnode = root->rightsibling;
		node_degree = root->degree;
		while( node_table[node_degree] )
		{
			assert( node_degree < num_nodes );
			node = node_table[node_degree];

			if( root == node )
			{
				printf( "Assert failed\n" );
			}

			if( islessthan( f, node, root ) )
			{
				/* swap the values */
				temp = root;
				root = node;
				node = temp;
			}

			node->cutcount = 0;
			node->rightsibling = node->leftsibling = node;

			adopt( root, node );

			node_table[node_degree] = NULL;
			++node_degree;
		}

		node_table[node_degree] = root;
		max_degree = ( node_degree > max_degree ) ? node_degree : max_degree;
		root = nextnode;
	}
	while( root && root != f->min );

	node = NULL;
	temp = NULL;

	f->min = NULL;
	for( idx = 0; idx <= max_degree; ++idx )
	{
		if( NULL != node_table[idx] )
		{
			node_table[idx]->rightsibling = node_table[idx]->leftsibling = node_table[idx];
			insert( f, node_table[idx] );
			++num_reinserted;
		}
	}

	/* reduce the number of nodes reinserted */
	f->numnodes -= num_reinserted;

	assert( f->numnodes == num_nodes );
	free( node_table );
}

void destroyheap( fibheap_t f )
{
    if( f )
    {
        free( f );
    }
}

void fiblog( loglevel_t level, const char* msg )
{
	static const char* level_str_table[LGL_MAX] = {
        "info",
        "warning",
        "error"
	};

	assert( msg );

	if( level >= LGL_INFO && level < LGL_MAX && msg )
	{
		fprintf( stderr, "%s] : %\n", level_str_table[level], msg );
	}
	else
	{
		fprintf( stderr, "%s\n", msg );
	}
}

void reducekeyval( fibheap_t f,
                   node_t *node,
                   heapkey_t delta )
{
    assert( f );

    switch( f->kind )
    {
        case KIND_INT:
            node->key.intdata -= delta.intdata;
            break;
        case KIND_FLOAT:
        	node->key.realdata -= delta.realdata;
            break;
        case KIND_GENERIC:
            assert( f->subtractor );
            ( *f->subtractor )( node->key, delta );
            break;
        default:
            assert( 0 );
    }
}

void updatemin( fibheap_t f, node_t *node )
{
    int is_min = 1;
	assert( f );
	assert( node );
	
	if( f->min )
	{
		is_min = islessthan( f, node, f->min );
	}

	if( is_min )
	{
		f->min = node;
	}
}

void insert( fibheap_t f, node_t *node )
{
    int is_min = 1;
    assert( f );

#ifdef _FIB_SHOW_OPS_
    printkey( f, node, "      INS>>" );
    printf( "\n" );
#endif

    if( f->min )
    {
        node->rightsibling = f->min->rightsibling;

        if( f->min->rightsibling )
        {
            f->min->rightsibling->leftsibling = node;
        }
        f->min->rightsibling = node;
        node->leftsibling = f->min;
    }

    updatemin( f, node );

    ++f->numnodes;
}

node_t *deletemin( fibheap_t f )
{
    node_t *ret = NULL;
    node_t *child = NULL;
    assert( f );

    /* delete the current min */
    if( f->min )
    {

#ifdef _FIB_SHOW_OPS_
        printf( "      DLM>>\n" );
        printkey( f, f->min, "HEAP MIN" );
        printf( "\n" );
#endif
        ret = f->min;

        /* cache child before update */
        child = f->min->firstchild;

        /* update the root-list */

        if( f->min == f->min->rightsibling ) /* the only root in the heap */
        {
            f->min = f->min->firstchild;
        }
        else
        {
        	f->min = removenode( f->min );
        }

        /* decrement the number of nodes in the heap */
        --f->numnodes;

        /* add the orphans to root-list only when
         * f->min is not the child itself
         */
        if( f->min && child && ( f->min != child ) )
        {
        	splicenodes( f->min, child );
            child->parent = NULL;
		}

        /* consolidate heap */
        consolidate( f );
    }

#ifdef _FIB_SHOW_OPS_
    if( f->min )
    {
        printf( "\n" );
        printkey( f, f->min, "HEAP MIN" );
        printf( "\n" );
    }
    printf( "      DLM END>>\n" );
#endif

    return ret;
}

void cut( fibheap_t f, node_t *node )
{
	node_t *parent;
    node_t *newchild;

	assert( f );
	assert( node );

	parent = node->parent;

	if( parent )
	{
		--parent->degree;
		++parent->cutcount;

		/* remove node from child list */
		newchild = removenode( node );

        /* make the returned child node the 
         * first child of parent 
         * if this was the only child then
         * newchild will be NULL
         */
        if( node == parent->firstchild )
        {
            parent->firstchild = newchild;
        }

		/* add node to rootlist */
        if( f->min )
        {
        	splicenodes( f->min, node );
        }
        else
        {
        	f->min = node;
        }

        /* reset the parent */
        node->parent = NULL;

        /* reset the cut count */
        node->cutcount = 0;
	}
}

void cascadingcut( fibheap_t f, node_t *node )
{
	node_t *parent;

	assert( node );
	parent = node->parent;

	if( parent )
	{
		if( parent->cutcount < MAX_CUT_COUNT )
		{
			++parent->cutcount;
		}
		else
		{
			cut( f, parent );
			cascadingcut( f, parent );
		}
	}
}

void decreasekey( fibheap_t f, node_t *node, heapkey_t delta )
{
	node_t *parent = NULL;

    assert( f );
    assert( node );

#ifdef _FIB_SHOW_OPS_
    printkey( f, node, "      DEK>>" );
    printf( "\n" );
#endif

    /* reduce the value of the node key */
    reducekeyval( f, node, delta );

    parent = node->parent;

    if( parent && islessthan( f, node, parent ) )
    {
		/* move to root list */
		cut( f, node );

		/* propagate cuts upwards if required */
		cascadingcut( f, parent );
    }

    /* update the heap min if required */
    updatemin( f, node );
}

node_t *findmin( fibheap_t f )
{
    node_t *ret = NULL;
    assert( f );
    if( f )
    {
        ret = f->min;
    }
    return ret;
}

void delete( fibheap_t f, node_t *node )
{
    heapkey_t delta;

    assert( f );
    assert( node );

#ifdef _FIB_SHOW_OPS_
    printkey( f, node, "   DEL>>" );
    printf( "\n" );
#endif

    /* make this node the node with the smallest value */
    if( f->min )
    {
        if( KIND_GENERIC == f->kind )
        {
            assert( f->copier );
            assert( f->subtractor );
            assert( f->iota );
            if( f->copier
             && f->subtractor
             && f->iota )
            {
                /* copy the heap min into the
                 * the delta
                 */
                ( *f->copier )( &delta, &node->key );
                
                /* subtract the min value from the 
                 * current value in the node
                 */
                ( *f->subtractor )( delta, f->min->key );

                /* subtract iota from the delta to 
                 * make it a value such that when
                 * this is subtracted from the current
                 * node value, the current node will 
                 * become the heap minimum
                 */
                ( *f->subtractor )( delta, *f->iota );
            }
            else
            {
                fiblog( LGL_ERRO, "Did not find copier or subtractor or iota for generic fheap" );
            }
        }
        else if( KIND_INT == f->kind )
        {
            delta.intdata = node->key.intdata - f->min->key.intdata - 1;
        }
        else if( KIND_FLOAT == f->kind )
        {
            delta.realdata = node->key.realdata - f->min->key.realdata - 1;
        }

        /* perform decrease key on the supplied node with new delta */
        decreasekey( f, node, delta );

        /* delete the node which now has become the heap min */
        deletemin( f ); 
    }   

#ifdef _FIB_SHOW_OPS_
    printf( "   DEL END>>\n" );
#endif
}

fibheap_t merge( fibheap_t firstheap, fibheap_t secondheap, fibheap_t *outheap )
{
    fibheap_t ret = *outheap;
    node_t *oldright = NULL;

    assert( firstheap );
    assert( secondheap );

    /* allow merging heaps only of the same kind */
    if( firstheap->kind != secondheap->kind )
    {
    	fiblog( LGL_ERRO, "Merging is allowed on heaps with the same kind" );
    	return ret;
    }

    assert( firstheap->min || secondheap->min );

    ret = createheap( outheap );

    if( ret )
    {
    	ret->kind = firstheap->kind;
    	ret->comparator = firstheap->comparator;
    	ret->subtractor = firstheap->subtractor;

    	/* splice the two root lists */
        if( firstheap->min && secondheap->min )
        {
            splicenodes( firstheap->min, secondheap->min );

            if( islessthan( firstheap,
                            firstheap->min, 
                            secondheap->min) )
    	    {
    		    ret->min = firstheap->min;
    	    }
    	    else
    	    {
    		    ret->min = secondheap->min;
    	    }
        }
        else
        {
            ret->min = ( firstheap->min ) ? firstheap->min : secondheap->min;
        }

        ret->numnodes = firstheap->numnodes + secondheap->numnodes;

    	destroyheap( firstheap );
    	destroyheap( secondheap );
    }
    return ret;
}

void printtree( fibheap_t f, node_t *node, int nodenum )
{
	node_t *child = NULL;

	if( node )
	{
		printkey( f, node, ">" );
        printf( "\n" );
		child = node->firstchild;

		if( !child )
		{
			return;
		}

        ++nodenum;

		do
		{
			printkey( f, child, ">>" );
            printf( " [%03d] ", nodenum );
            printtree( f, child, nodenum );
			child = child->rightsibling;
		}
		while( child && child != node->firstchild );
	}
}

void dumpheap( fibheap_t f )
{
	node_t  *node = NULL;
    assert( f );
    
    node = f->min;

    if( !node )
    {
    	return;
    }

    printf( "\n----------------------------\n" );
    printf(   "------ HEAP DUMP START -----\n" );
    printf( "# num elems: %d\n", f->numnodes );
    printkey( f, f->min, "HEAP MIN" );
    printf( "\n" );
	do
	{
//		printtree( f, node, 0 );
		node = node->rightsibling;
		printkey( f, node, "  " );
		printf( "\n" );
    }
	while( node && node != f->min );
    printf( "\n------ HEAP DUMP END  ------\n" );
}

/* end of file */

