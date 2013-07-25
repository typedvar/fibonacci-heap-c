/*
 * author     : avinandan sengupta
 * reg no     : 2010CSY7543
 * course     : CSL630
 * assignment : Fibonacci heap
 * file       : testers.c
 * purpose    : Fibonacci heap testers for
 *              various key types
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "fibheap.h"
#include "fibdefines.h"

int compare_strings( heapkey_t lhs, heapkey_t rhs )
{
    char* lhs_str = ( char* )lhs.genericdata;
    char* rhs_str = ( char* )rhs.genericdata;

    return strcmp( lhs_str, rhs_str );
}

void test_float_heap()
{
    int i = 0;
    int delidx = 0;
    float store[] = { 0.99, 2.3, 80098.9, 5, 1.3, 6, -2100.8, 15.2, 100.5, 53, 5.9, -100.009 };
    int num_elems = sizeof( store ) / sizeof( store[0] );
    node_t *node = NULL;
    node_t *min = NULL;

    node_t *todel[2] = { NULL, NULL };

    heapkey_t data;
    fibheap_t heap = NULL;
    heap = createheap( &heap );
    setkind( heap, KIND_FLOAT );

    printf( "Inserting: " );
    for( i = 0; i < num_elems ; ++i )
    {
    	printf( "%0.2f, ", store[i] );
        data.realdata = store[i];
        node = createnode( data );
        insert( heap, node );

        if( store[i] == 100.5 
         || store[i] == 6 )
        {
            todel[delidx++] = node;
        }
    }

    dumpheap( heap );
    printf( "\n" );

    for( i = 0; i < delidx; ++i )
    {
        delete( heap, todel[i] );
    }

//    for( i = 0; i < num_elems ; ++i )
//    {
//		min = deletemin( heap );
//
//		if( min )
//		{
//			printf( "\nmin is : %f\n", min->key.realdata );
//		}
//		destroynode( min );
//    }
    dumpheap( heap );
    destroyheap( heap );
}

void test_int_heap()
{
    int i = 0;
    int store[] = { 9, 2, 8, 5, 1, 6, -21, 15, 100, 53, 5, -100 };
    int num_elems = sizeof( store ) / sizeof( store[0] );
    node_t *node = NULL;
    node_t *min = NULL;

    heapkey_t data;
    fibheap_t heap = NULL;
    heap = createheap( &heap );

    printf( "Inserting: " );
    for( i = 0; i < num_elems ; ++i )
    {
    	printf( "%d, ", store[i] );
        data.intdata = store[i];
        node = createnode( data );
        insert( heap, node );
    }
    printf( "\n" );

    for( i = 0; i < num_elems ; ++i )
    {
		min = deletemin( heap );

		if( min )
		{
			printf( "\nmin is : %d\n", min->key.intdata );
		}
		destroynode( min );
    }
    dumpheap( heap );
    destroyheap( heap );
}

void test_string_heap()
{
    unsigned int i = 0;
    unsigned int j = 0;
    node_t *node = NULL;
    heapkey_t data;
    fibheap_t heap = NULL;
    fibheap_t heap1 = NULL;
    fibheap_t out = NULL;

    char* test_strings[] = {
          "virgo"
        , "scorpio"
        , "taurus"
        , "leo"
        , "createheap"
        , "consolidate"
        , "destroyheap"
        , "setkind"
        , "getkind"
        , "setcomparator"
        , "getcomparator"
        , "islessthan"
        , "insert"
        , "deletemin"
        , "decreasekey"
        , "findmin"
        , "delete"
        , "merge"
        , "setkeyprinter"
        , "getprinter"
        , "dumpheap"
        , NULL
    };

    char* test_string2[] = {
          "virgo"
        , "scorpio"
        , "abustil"
        , "taurus"
        , "leo"
        , NULL
    };

    heap = createheap( &heap );
    setkind( heap, KIND_GENERIC );
    setcomparator( heap, &compare_strings );

    for( i = 0; test_strings[i]; ++i )
    {
        data.genericdata = test_strings[i];
        node = createnode( data );
        insert( heap, node );
    }

    printf( "\nMin element is %s \n", ( char* )( findmin( heap )->key.genericdata ) );

    heap1 = createheap( &heap1 );
    setkind( heap1, getkind( heap ) );
    setcomparator( heap1, getcomparator( heap ) );

    for( j = 0; test_string2[j]; ++j )
    {
        data.genericdata = test_string2[j];
        node = createnode( data );
        insert( heap, node );
    }

    /* this will automatically destryo heap and heap1 */
    merge( heap, heap1, &out );

    printf( "Min element in merged heap is %s \n", ( char* )( findmin( out )->key.genericdata ) );

    destroyheap( out );
}

/* end of file */

