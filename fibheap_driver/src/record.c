/*
 * author     : avinandan sengupta
 * reg no     : 2010CSY7543
 * course     : CSL630
 * assignment : Fibonacci heap
 * file       : records.c
 * purpose    : implementation for manipulating records
 */

#include <stdlib.h>
#include <memory.h>
#include "record.h"

record_t *create_record()
{
    record_t *record = NULL;

    record = ( record_t* )malloc( sizeof( record_t ) );
    memset( record, 0x0, sizeof( record_t ) );
    return record;
}
/* end of file */

