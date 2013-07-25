/*
 * author     : avinandan sengupta
 * reg no     : 2010CSY7543
 * course     : CSL630
 * assignment : Fibonacci heap
 * file       : record.h
 * purpose    : defines the file format
 *              and associated record structure
 */

#ifndef _record_v1_h_
#define _record_v1_h_

/* record structure
         1         2         3         4         5
12345678901234567890123456789012345678901234567890
iiii---ccccccc---ffff--------cccccccc--ddd--------

*/

typedef enum df_endian
{
    DF_BIG_ENDIAN,
    DF_LITTLE_ENDIAN
} df_endian_t;

/* field sizes */
enum field_sizes
{
    CMD_SIZE = sizeof( int ),
    FILLER0_SIZE = 3,
    FIBKEY_SIZE = 7,
    FILLER1_SIZE = 3,
    HTKEY_SIZE = sizeof( float ),
    FILLER2_SIZE = 8,
    DATA_SIZE = 8,
    FILLER3_SIZE = 2,
    FLD2_SIZE = 3,
    FILLER4_SIZE = 8
};

enum record_size {
    REC_SIZE = 
      CMD_SIZE
    + FILLER0_SIZE
    + FIBKEY_SIZE    
    + FILLER1_SIZE
    + HTKEY_SIZE
    + FILLER2_SIZE
    + DATA_SIZE
    + FILLER3_SIZE
    + FLD2_SIZE
    + FILLER4_SIZE
};

enum start_marks {
    CMD_START = 0,
    FIBKEY_START = CMD_SIZE + FILLER0_SIZE,
    HTKEY_START = FIBKEY_START + FIBKEY_SIZE + FILLER1_SIZE,
    DATA_START = HTKEY_START + HTKEY_SIZE + FILLER2_SIZE,
    FLD2_START = DATA_START + DATA_SIZE + FILLER3_SIZE
};

/* definition for the byte type */
typedef char byte_t;

/* command types 
1 - insert record
2 - Delete Min
3 - Decrease Key
4 - Delete Record
5 - Dump 

*/
typedef enum commands
{
    CMD_UNKNOWN = 0,
    CMD_INSERT = 1,
    CMD_DELMIN = 2,
    CMD_DECKEY = 3,
    CMD_DELETE = 4,
    CMD_DUMP   = 5,
    CMD_MAX
} command_t;

/* the insert record type */
typedef struct insertrec
{
    byte_t str0[FIBKEY_SIZE];
    float  key;
    byte_t str1[DATA_SIZE];
    byte_t str2[FLD2_SIZE];
} insertrec_t;

/* the record composite */
typedef struct record
{
    command_t command;
    union recdata
    {
        insertrec_t insert_rec;
    } data;
} record_t;

/* create_record
 * allocates memory for a record type
 * and initializes it
 */
record_t *create_record();

/* delete_record
 * destroys a record type
 */
void delete_record( record_t *p_record );

#endif 
/* end of file */

