/**
 *  CSE 100 PA3 3: Huffman Compress/Decompress and Code Refactoring
 *  Author: Peter Phan A13042904 cs100wdh
 *
 */
#ifndef BITINPUTSTREAM_H
#define BITINPUTSTREAM_H

#include <iostream>
#include <fstream>


/**
 * Class that allows user to read from a file one bit at a time 
 * by using istream and then buffering a bit at a time
 */

class BitInputStream{
private:
    char buff; //buffer hodling current byte
    int nbits; //keeps track of which bits are read
    std::istream& in; //iostream used to read from file

public:
    //constructor such that implementation wraps arund ifstream
    BitInputStream(std::ifstream& is ) : in(is), buff(0), nbits(0) {}

    /** Method to extract next byte from stream
     */ 
    void fill();
    
    /** Reads from buffer left to right
     */ 
    int readBit();
};

#endif //BITINPUTSTREAM_H
