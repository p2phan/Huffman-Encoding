/*
 * Filename: BitInputStream.cpp
 * Author: Peter Phan cs100wdh A13042904
 *
 * Purpose: Designed to read a file one bit at a time
 * by using istream and a buffer
 */

#include "BitInputStream.h"
#include <bitset>

/**
 * Purpose when the buffer becomes full, this is called to get next
 * byte from file
 *
 */

void BitInputStream::fill()
{
    //resets buffer
    buff = in.get();
    nbits = 0;
}

/**
 * Returns the next bit from a file
 */

int BitInputStream::readBit()
{
    //check if we read all bits yet
    if(nbits == 8)
    {
        fill();
    }

    //updates nbits and return current bit
    int bit = (buff >> (7 - nbits)) & 1;    
    nbits ++;
    return bit;    

}



