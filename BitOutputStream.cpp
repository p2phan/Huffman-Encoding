/**
 * Filename: BitOutputStream.h
 * Author: Peter Phan A13042904	cs100wdh
 *
 * Purpose: Allows user to write to file one bit at a a time
 *
 */

#include "BitOutputStream.h"
#include <bitset>

/** 
 * when buffer is full, it writes the buffer to a file
 */
void BitOutputStream::flush()
{
    std::bitset<8> buffB(buff);
 //   std::cout << buffB  << " printing  " << std::endl;
    out.put(buff);
    //what does this line do???
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
    
    int bit = i & 1;
    
    //std::cout << bit << " with nbits " << nbits << std::endl;
    buff |= (bit << (7-nbits));
    nbits++;   
}

