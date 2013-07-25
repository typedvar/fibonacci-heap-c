/*
 * author     : avinandan sengupta
 * reg no     : 2010CSY7543
 * course     : CSL630
 * assignment : Fibonacci heap
 * file       : file_reader.h
 * purpose    : declaration for the record
 *              processing functions
 */

#ifndef _file_reader_h_
#define _file_reader_h_

#include <stdio.h>
#include "record.h"

/* operations of the file */
record_t *read_record( FILE *p_file, record_t *p_record, df_endian_t endianness );

#endif

/* end of file */
