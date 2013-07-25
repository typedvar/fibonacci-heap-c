/*
 * author     : avinandan sengupta
 * reg no     : 2010CSY7543
 * course     : CSL630
 * assignment : Fibonacci heap
 * file       : data_processor.h
 * purpose    : declaration for the file data
 *              processing entry function
 */

#ifndef _data_processor_h_
#define _data_processor_h_

#include "fibheap.h"
#include "record.h"

void process_data_file( const char* p_data_file, df_endian_t endianness );

#endif
