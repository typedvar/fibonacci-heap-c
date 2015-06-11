/*
 * author     : avinandan sengupta
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
