/*
 * author     : avinandan sengupta
 * reg no     : 2010CSY7543
 * course     : CSL630
 * assignment : Fibonacci heap
 * file       : functors.c
 * purpose    : callback function implementations
 */

#include <stdio.h>
#include <assert.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <math.h>

#include "fibheap.h"
#include "fibdefines.h"
#include "record.h"
#include "file_reader.h"
#include "hashtable.h"
#include "hashfunc.h"

#if 0
void print_key_f50( char* indent, heapkey_t lhs )
{
	insertrec_t *insrec = ( insertrec_t* )lhs.genericdata;
	assert( insrec );
	printf( "%s ", indent );
	printf( "field 2: %.*s ", DATA_SIZE, insrec->str1 );
	printf( "field 1: %.*s ", FIBKEY_SIZE, insrec->str0 );
	printf( "datakey: %09.3lf ", insrec->key );
	printf( "field 3: %.*s ", FLD2_SIZE, insrec->str2 );
}
#endif

void print_key( char* indent, heapkey_t lhs )
{
	insertrec_t *insrec = ( insertrec_t* )lhs.genericdata;
	assert( insrec );
	printf( "%s ", indent );
    printf( "fibkey:%5d ", insrec->fib_key );
    printf( "htkey :%5d ", insrec->ht_key );
    printf( "data  :%c.%c%c ", insrec->data[0], insrec->data[1], insrec->data[2] );
}

int compare_records( heapkey_t lhs, heapkey_t rhs )
{
	int retval = 0;
    insertrec_t *reclhs = NULL;
    insertrec_t *recrhs = NULL;

	assert( lhs.genericdata );
	assert( rhs.genericdata );

	reclhs = ( insertrec_t* )lhs.genericdata;
	recrhs = ( insertrec_t* )rhs.genericdata;

    retval = reclhs->fib_key - recrhs->fib_key;
	return retval;
}

int compare_strings_ht( htkey_t lhs, htkey_t rhs )
{
    int ret = 1;
    if( lhs && rhs )
    {
        ret = memcmp( lhs, rhs, DATA_SIZE * sizeof( char ) );
    }
    return ret;
}

int compare_int_ht( htkey_t lhs, htkey_t rhs )
{
    int ret = 1;
    int lhsint = 0;
    int rhsint = 0;
    if( lhs && rhs )
    {
        lhsint = *( int* )lhs;
        rhsint = *( int* )rhs;
        ret = lhsint - rhsint;
    }
    return ret;
}

htkey_t copy_key_ht( htkey_t source, memop_t mop )
{
    htkey_t copy = NULL;

    if( MOP_ALLOC == mop )
    {
        copy = malloc( HTKEY_SIZE * sizeof( char ) );
        memcpy( copy, source, HTKEY_SIZE * sizeof( char ) );
    }
    else if( MOP_DELETE == mop )
    {
        if( source )
        {
            free( source );
        }
    }
    return copy;
}

heapkey_t subtract_key( heapkey_t key, heapkey_t delta )
{
    insertrec_t *minuend = ( insertrec_t *)key.genericdata;
    insertrec_t *subtrahend = (insertrec_t *)delta.genericdata;

    minuend->fib_key += subtrahend->fib_key;

    return key;
}

void copy_key( heapkey_t *destination, heapkey_t *source )
{
    insertrec_t *keydata = ( insertrec_t* )malloc( sizeof( insertrec_t ) );
    memcpy( keydata, source->genericdata, sizeof( insertrec_t ) );
    destination->genericdata = keydata;
}

unsigned int intkeyhasher( htkey_t key )
{
	char* strkey = ( char* )key;
    unsigned int hash = 5381;
    int c;
    int idx = 0;

    while( idx < 4 )
    {
        c = strkey[idx++];
        hash = ( ( hash << 5 ) + hash ) + c;
    }

	return hash;
}

unsigned int fltkeyhasher( htkey_t key )
{
	float num = ( float ) *( float* )( &key );
	unsigned int intkey = ( unsigned int ) *( unsigned int* )( &num );
	return hashcore( intkey );
}

unsigned int strkeyhasher( htkey_t key )
{
	char* strkey = ( char* )key;
    unsigned int hash = 5381;
    int c;

    while( c = *strkey++ )
    {
        hash = ( ( hash << 5 ) + hash ) + c;
    }

	return hash;
}

/* end of file */
