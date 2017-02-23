/*
 * Filename: BitInputStream.cpp
 * Author: Peter Phan cs100wdh A13042904
 *
 * Purpose: Designed to read a file one bit at a time
 *
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
 //   std::bitset<8> buffB(buff);
   // std::cout << buffB << " is read"<< std::endl;
    nbits = 0;
   //std::cout << "cut" << std::endl;    
}

/**
 * Returns the next bit from a file
 *
 *
 *
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
   // std::cout << ((buff >> (7 - nbits)) & 1) << " with "<< nbits << std::endl;    
    nbits ++;
    return bit;    

}



