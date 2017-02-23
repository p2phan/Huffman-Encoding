/**
 * Filename: BitOutputStream.h
 * Author: Peter Phan A13042904	cs100wdh
 *
 * Purpose: Allows user to write to file one bit at a a time
 * by using ostream and a buffer
 */

#include "BitOutputStream.h"
#include <bitset>

/** 
 * When buffer is full, it writes the buffer to a file
 */
void BitOutputStream::flush()
{
    //we write out what on the buffer
    out.put(buff);
    out.flush();
    buff = nbits = 0;
}

/**
 * Puts bit in buffer from left to right
 *
 * Parmeter: 
 *          i: the bit to put into buffer
 */
void BitOutputStream::writeBit(int i)
{
    //when buffer is full we reset buffer 
    if(nbits == 8)
    {
        flush();
    }
   
    //puts bit in buffer left to right and updates nbits 
    int bit = i & 1;
    
    buff |= (bit << (7-nbits));
    nbits++;   
}

