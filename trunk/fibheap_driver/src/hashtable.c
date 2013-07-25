/*
 * author     : avinandan sengupta
 * reg no     : 2010CSY7543
 * course     : CSL630
 * assignment : Fibonacci heap
 * file       : hashtable.c
 * purpose    : hash table implementation
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "hashtable.h"
#include "record.h"

#define DEFAULT_NUM_BUCKETS 200

typedef struct bucket bucket_t;
struct bucket
{
	htkey_t key;
	value_t val;
	bucket_t *next;
};

typedef struct hashtable
{
	size_t numelems;
	size_t numbuckets;

	/* array of buckets */
	bucket_t **buckets;

	/* the hash function */
	hashfunc_t hasher;

	/* the key comparator */
	htkeycomparator_t keycomp;

    /* the key copier */
    htkeyallocator_t keyallocator;

} hashtable_internal_t;

int isemptyht( hashtable_t ht )
{
	assert( ht );
	return ( ht->numelems > 0 ? 0 : 1 );
}

size_t getsizeht( hashtable_t ht )
{
	assert( ht );
	return ht->numbuckets;
}

bucket_t *createbucket( hashtable_t ht, htkey_t key, value_t val )
{
	bucket_t *bucket = NULL;

    assert( ht );
    assert( ht->keyallocator );
    
    bucket = ( bucket_t* )malloc( sizeof( bucket_t ) );
	assert( bucket );

    bucket->key = ( *ht->keyallocator )( key, MOP_ALLOC );
	bucket->val = val;
	bucket->next = NULL;

    return bucket;
}

void destroybucket( hashtable_t ht, bucket_t *bucket )
{
	if( bucket )
	{
        if( bucket->key )
        {
            ( *ht->keyallocator )( bucket->key, MOP_DELETE );
        }
		free( bucket );
	}
}

hashtable_t createht( size_t numbuckets )
{
	hashtable_t ht = NULL;

	ht = ( hashtable_t )malloc( sizeof( hashtable_internal_t ) );

	if( numbuckets <= 0 )
	{
		numbuckets = DEFAULT_NUM_BUCKETS;
	}

	ht->numelems = 0;
	ht->numbuckets = numbuckets;
	ht->buckets = ( bucket_t** )calloc( numbuckets, sizeof( bucket_t* ) );
	ht->hasher = NULL;
	ht->keycomp = NULL;
    ht->keyallocator = NULL;

	return ht;
}

void deleteht( hashtable_t ht )
{
	assert( ht );
	if( ht )
	{
		free( ht );
	}
}

void installkv( hashtable_t ht, htkey_t key, value_t val )
{
	unsigned int idx = 0;
    bucket_t *slot = NULL;
    bucket_t *newslot = NULL;

    assert( ht );
	assert( ht->hasher );

    idx = ( *ht->hasher )( key );
	idx %= ht->numbuckets;

	slot = ht->buckets[idx];
	newslot = createbucket( ht, key, val );

	if( slot )
	{
#ifdef _DEBUG
		printf( "COLLISION: %.*s\n", DATA_SIZE, ( char* )key );
#endif
		slot->next = newslot;
	}
	else
	{
		ht->buckets[idx] = newslot;
	}
	++ht->numelems;
}

value_t lookupcore( hashtable_t ht, htkey_t key, int delkey )
{
	value_t val = NULL;
	unsigned int idx = 0;
	bucket_t *slot = NULL;
	bucket_t *prevslot = NULL;

	assert( ht );
	assert( ht->hasher );

	idx = ( *ht->hasher )( key );
	idx %= ht->numbuckets;

	slot = ht->buckets[idx];
	
	while( slot )
	{
        assert( ht->keycomp );
		if( 0 == ( *ht->keycomp )( key, slot->key ) )
		{
			val = slot->val;

			if( delkey == 1 )
			{
				/* remove key from hashtable */
				if( !prevslot )
				{
					ht->buckets[idx] = slot->next;
				}
				else
				{
					prevslot->next = slot->next;
				}
				--ht->numelems;
			}
			break;
		}
		prevslot = slot;
		slot = slot->next;
	}

	if( delkey == 1 && val )
	{
		destroybucket( ht, slot );
	}
	return val;
}

value_t lookupkv( hashtable_t ht, htkey_t key )
{
	return lookupcore( ht, key, 0 );
}

value_t removekv( hashtable_t ht, htkey_t key )
{
	return lookupcore( ht, key, 1 );
}

void sethashfunc( hashtable_t ht, hashfunc_t hashfunc )
{
	assert( ht );
	ht->hasher = hashfunc;
}

hashfunc_t gethashfunc( hashtable_t ht )
{
	assert( ht );
	return ht->hasher;
}

void sethtkeycomparator( hashtable_t ht, htkeycomparator_t keycomp )
{
	assert( ht );
	ht->keycomp = keycomp;
}

htkeycomparator_t gethtkeycomparator( hashtable_t ht )
{
	assert( ht );
	return ht->keycomp;
}

void sethtkeyallocator( hashtable_t ht, htkeyallocator_t keyallocator )
{
    assert( ht );
    ht->keyallocator = keyallocator;
}

htkeyallocator_t gethtkeyallocator( hashtable_t ht )
{
    assert( ht );
    return ht->keyallocator;
}

/* end of file */

