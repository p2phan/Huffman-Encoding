#ifndef BITINPUTSTREAM_H
#define BITINPUTSTREAM_H

#include <iostream>
#include <fstream>


/**
 * 
 *
 */

class BitInputStream{
private:
    char buff;
    int nbits;
    std::istream& in; 

public:
    BitInputStream(std::ifstream& is ) : in(is), buff(0), nbits(0) {}

    void fill();
    
    int readBit();
};

#endif //BITINPUTSTREAM_H
