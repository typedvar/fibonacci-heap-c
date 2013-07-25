/*
 * author     : avinandan sengupta
 * reg no     : 2010CSY7543
 * course     : CSL630
 * assignment : Fibonacci heap
 * file       : hashfunc.c
 * purpose    : hash function for floats
 */
#include <math.h>
#include <stdio.h>

unsigned int shrotl( unsigned int num, int bits )
{
    if( ( bits &= 31 ) == 0 )
    {
        return num;
    }
    return ( num << bits ) | ( num >> ( 32 - bits ) );
}

unsigned int hashcore( unsigned int subject )
{
    subject = abs( subject );
    subject *= 37;
    subject = shrotl( subject, 5 );
	return subject;
}

/* end of file */

