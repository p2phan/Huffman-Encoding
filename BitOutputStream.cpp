/**
 * Dummy
 *
 *
 */

#include "BitOutputStream.h"

void BitOutputStream::flush()
{
    out.put(buff);
    //what does this line do???
    out.flush();
    buff = nbits = 0;
   // std::cout << "cut" << std::endl;
}

void BitOutputStream::writeBit(int i)
{
    if(nbits == 8)
    {
        flush();
    }
    
    int bit = i & 1;
    
    //std::cout << bit << " with nbits " << nbits <<std::endl;
    buff += (bit << (7-nbits));
    nbits++;   
}

