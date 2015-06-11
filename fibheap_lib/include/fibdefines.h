/*
 * author     : avinandan sengupta
 * file       : fibdefines.h
 * purpose    : top level macros and
 *              constants
 */

#ifndef _fibdefines_h_
#define _fibdefines_h_

/* setting this to 1 makes the implementation
 * a Fibonacci heap
 */
#define MAX_CUT_COUNT 1

/* a million nodes */
#define MAX_NODES  2

/* the value of phi */
#define FIB_PHI 1.61803

/* xor swapper */
#define SWAP( X, Y ) \
	X ^= Y; Y ^= X; X ^= Y;

/* tolerance for float comparisons */
#define FIB_FLT_ZERO 0.000001

//#define _INT_KEYS_

#endif

/* end of file */

