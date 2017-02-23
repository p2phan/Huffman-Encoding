/**
 *  CSE 100 PA3 3: Huffman Compress/Decompress and Code Refactoring
 *  Author: Peter Phan A13042904 cs100wdh
 *
 */
#ifndef BITOUTPUTSTREAM_H
#define BITOUTPUTSTREAM_H

#include <iostream>

/**
 * A class that allows users to "write a bit" at a time
 * by using ostream and then buffering a bit at a time
 */

class BitOutputStream{
private:
    char buff; // the buffer to hold bits
    int nbits; // keeps track of when to reset
    std::ostream& out; //stream to write to

public:

    //constructor that wraps it's funcitonality around the ostream
    BitOutputStream(std::ostream& ostr) : out(ostr), buff(0), nbits(0) {}

    /** Writes to a file when the buffer is full
     */ 
    void flush();

    /** Puts in bits to the buffer from left to right
     *
     */ 
    void writeBit(int i);

};

#endif //BITOUTPUTSTREAM_H
