/*
 * author     : avinandan sengupta
 * reg no     : 2010CSY7543
 * course     : CSL630
 * assignment : Fibonacci heap
 * file       : data_processor.c
 * purpose    : processes the data file
 */

#include <stdio.h>
#include <assert.h>
#include <stdio.h>
#include <memory.h>

#include "fibheap.h"
#include "fibdefines.h"
#include "hashtable.h"
#include "record.h"
#include "file_reader.h"
#include "functors.h"

void process_record( fibheap_t heap, hashtable_t ht, record_t *record )
{
    node_t *node = NULL;
    node_t *foundnode = NULL;
    heapkey_t data;
    int htkey = 0;
    static int cmdcount = 0;

    assert( heap );
    assert( ht );
    assert( record );

    data.genericdata = &( record->insert_rec );
    htkey = record->insert_rec.ht_key;
    ++cmdcount;

#ifdef _DEBUG
    printf( "  %06d] cmd:%d, fk:%d, htk:%d\n", cmdcount, record->command, record->insert_rec.fib_key, record->insert_rec.ht_key );
#endif

    printf( "[record number %d]", cmdcount );
    switch( record->command )
    {
    case CMD_INSERT:
        node = createnode( data );
        foundnode = lookupkv( ht, &htkey );
        if( !foundnode )
        {
        	insert( heap, node );
        	installkv( ht, &htkey, node );
        }
        else
        {
            printf( "WARN: duplicate key insert %d [record number: %d]\n", htkey, cmdcount );
        	destroynode( node );
        }
        break;
    case CMD_DELMIN:
        node = deletemin( heap );
        if( node )
        {
            data.genericdata = node->key.genericdata;
            htkey = ( ( insertrec_t* )data.genericdata )->ht_key;
            foundnode = removekv( ht, &htkey );
            destroynode( node );
        }
        break;
    case CMD_DECKEY:
        node = lookupkv( ht, &htkey );
        if( node )
        {
            if( ( ( insertrec_t* )data.genericdata )->fib_key < 0 )
            {
                decreasekey( heap, node, data );
            }
            else
            {
                printf( "WARN: Invalid delta (>0) in decrease key [record number: %d]\n", cmdcount );
            }
        }
        break;
    case CMD_DELETE:
    	node = removekv( ht, &htkey );
    	if( node )
    	{
    		delete( heap, node );
    	}
    	else
    	{
    		printf( "WARN: trying to remove invalid key %d\n", htkey );
    	}
        break;
    case CMD_DUMP:
        dumpheap( heap );
        break;
    default:
        printf( "WARN: Invalid control command: %d\n", record->command );
    }
}

void process_data_file( const char* p_data_file, df_endian_t endianness )
{
    fibheap_t heap = NULL;
    hashtable_t ht = NULL;

    insertrec_t *insrec = NULL;
    heapkey_t *iota = NULL;
    size_t numrecords = 0;

    /* open data file */
    FILE* file = fopen( p_data_file, "rb" );

//#ifdef _DEBUG
//    /* print field sizes */
//    printf( "CM:%d\nF1:%d\n K:%d\nF2:%d\nF3:%d\n",
//        CMD_START,
//        FIBKEY_START,
//        HTKEY_START,
//        DATA_START,
//        FLD2_START );
//#endif

    if( file )
    {
    	fseek( file, 0, SEEK_END );
    	numrecords = ftell( file );
    	fseek( file, 0, SEEK_SET );

    	numrecords /= REC_SIZE;

    	/* create the hash table */
    	ht = createht( numrecords );
    	if( ht )
    	{
    		sethashfunc( ht, &intkeyhasher );
    		sethtkeycomparator( ht, &compare_int_ht );
            sethtkeyallocator( ht, &copy_key_ht );
    	}

        heap = createheap( &heap );
#ifdef _INT_KEYS_
    	/* create the heap */
        setkind( heap, KIND_INT );
#else
        setkind( heap, KIND_GENERIC );
        setcomparator( heap, &compare_records );
        setkeyprinter( heap, &print_key );
        setcopier( heap, &copy_key );
        setsubtractor( heap, &subtract_key );

        /* create iota of 1 int */
        iota = ( heapkey_t *)malloc( sizeof( heapkey_t ) );
        insrec = ( insertrec_t* )malloc( sizeof( insertrec_t ) );
        memset( insrec, 0x0, sizeof( insertrec_t ) );
        insrec->fib_key = -1;
        iota->genericdata = insrec;

        setiota( heap, iota );
#endif

        if( heap )
        {
            while( !feof( file ) )
            {
                record_t *record = create_record();
                read_record( file, record, endianness );

                if( record->command > CMD_UNKNOWN
                 && record->command < CMD_MAX )
                {
                    process_record( heap, ht, record );
                }
            }
        }
        fclose( file );
    }
}

/* end of file */
