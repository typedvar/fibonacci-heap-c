/*
 * author     : avinandan sengupta
 * reg no     : 2010CSY7543
 * course     : CSL630
 * assignment : Fibonacci heap
 * file       : fibheap_main.c
 * purpose    : Fibonacci heap driver program
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

//#define _USE_TEST_DATA_
#define _USE_REAL_DATA_

#ifdef _USE_TEST_DATA_
#include "testers.h"
#endif

#ifdef _USE_REAL_DATA_
#include "data_processor.h"
#endif

int main( int argc, char* argv[] )
{
#ifdef _USE_REAL_DATA_
    const char* data_file = NULL;
    df_endian_t endianness = DF_BIG_ENDIAN;
    if( argc < 2 || argc > 3 )
    {
        printf( "usage: %s <data file> [l|b]\n"
                "       l = little endian data file\n"
                "       b = big endian data file\n"
                "           default b\n", argv[0] );
        return 1;
    }
    data_file = argv[1];

    if( argc == 3 && ( argv[2][0] == 'l' || argv[2][0] == 'L' ) )
    {
        endianness = DF_LITTLE_ENDIAN;
    }
    process_data_file( data_file, DF_BIG_ENDIAN );
#endif

#ifdef _USE_TEST_DATA_
    test_int_heap();
    test_float_heap();
    test_string_heap();
#endif
    return 0;
}

/* end of file */

