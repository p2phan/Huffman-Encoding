/*
 * Dummy
 */

#include "BitInputStream.h"


void BitInputStream::fill()
{
    buff = in.get();
    nbits = 0;
    std::cout << "cut" << std::endl;    
}



int BitInputStream::readBit()
{
    if(nbits == 8)
    {
        fill();
    }

    int bit = (buff >> (7 - nbits)) & 1;    
    nbits ++;
    
    std::cout << ((buff >> (7 - nbits)) & 1) << " with "<< nbits << std::endl;    
    return bit;    

}



