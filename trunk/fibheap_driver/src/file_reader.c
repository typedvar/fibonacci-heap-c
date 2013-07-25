/*
 * author     : avinandan sengupta
 * reg no     : 2010CSY7543
 * course     : CSL630
 * assignment : Fibonacci heap
 * file       : file_reader.c
 * purpose    : file data reader
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "file_reader.h"
#include "fibdefines.h"

df_endian_t gethostendianness()
{
    return DF_LITTLE_ENDIAN;
}

int read_int( byte_t *buff, size_t size, df_endian_t endianness )
{
    char btemp[CMD_SIZE];
    int  ret = 0;

    memcpy( btemp, buff, size );
    if( gethostendianness() != endianness )
    {
        /* swap 1 / 4 */
        SWAP( btemp[0], btemp[3] );

        /* swap 2 / 3 */
        SWAP( btemp[1], btemp[2] );
    }
    ret = ( int )( *btemp );
    return ret;
}

float read_float( byte_t *buff, size_t size, df_endian_t endianness )
{
    char btemp[HTKEY_SIZE];
    float ret = 0;

    memcpy( btemp, buff, size ); 
    if( gethostendianness() != endianness )
    {
        /* swap 1 / 4 */
        SWAP( btemp[0], btemp[3] );
        /* swap 2 / 3 */
        SWAP( btemp[1], btemp[2] );
    }
    ret = ( float )( *btemp );
    return ret;
}

record_t *read_record( FILE *p_file, record_t *p_record, df_endian_t endianness )
{
    byte_t buff[REC_SIZE] = { 0 };
    assert( p_file );
    assert( p_record );

	fread( buff, REC_SIZE, 1, p_file );
    p_record->command = read_int( buff + CMD_START, CMD_SIZE, endianness );

    if( CMD_INSERT == p_record->command 
     || CMD_DELETE == p_record->command
     || CMD_DECKEY == p_record->command )
    {
        p_record->insert_rec.fib_key = read_int( buff + FIBKEY_START, FIBKEY_SIZE, endianness );
        p_record->insert_rec.ht_key = read_int( buff + HTKEY_START, HTKEY_SIZE, endianness );
        memcpy( p_record->insert_rec.data, buff + DATA_START, DATA_SIZE );
    }

    return p_record;
}
/* end of file */

