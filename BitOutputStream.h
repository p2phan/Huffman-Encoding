#ifndef BITOUTPUTSTREAM_H
#define BITOUTPUTSTREAM_H

#include <iostream>



/**
 * Dummy file for checkpoint
 *
 */

class BitOutputStream{
private:
    char buff;
    int nbits;
    std::ostream& out;

public:

    BitOutputStream(std::ostream& ostr) : out(ostr), buff(0), nbits(0) {}

    void flush();

    void writeBit(int i);

};

#endif //BITOUTPUTSTREAM_H
