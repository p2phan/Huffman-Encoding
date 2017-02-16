#include "HCTree.h"
#include<iostream>
#include<fstream>

/**
 * Filename: compress.cpp
 * Author: Peter Phan
 * Purpose: To compress files using huffman implementation 
 *
 */

/**
 * Takes in a file, encode it and puts the encode file to an output file
 *
 */
int main(int argc, char* argv[])
{
    
    //checks arg
    if(argc != 3){
        cout << "Invalid number of arguments\n"
             << "Usage ./compress <file to be compressed> <output file>\n"; 
        return -1;
    }

    //stream to read file
    ifstream original;
    original.open(argv[1]);

    //checks if file exist
    if(!original.is_open()){
        cout << "Failed to open " << argv[1] << endl;
        return -1;
    }

    //vector to be filled with frequency of each byte in input file
    vector<int> freq(256, 0);
    while(1)
    {
        byte count = original.get();
        if(original.eof()){ break;}
        freq.at(count)++;
    }

    //writes out freq onto output file
    ofstream compress;
    compress.open(argv[2]);   
    for(int i = 0; i < freq.size(); i++)
    {
        compress << freq[i] << endl;
    }

    //builds tree to encode
    HCTree ht;
    ht.build(freq);
    original.clear();
    original.seekg(0, ios::beg);

    //encodes to putput file
    while(1)
    {
        byte symbol = original.get();
        if(original.eof()){ break;}
        ht.encode(symbol, compress);
        //cout << "putting c in" << endl;
    }
   
    original.close(); 
    compress.close();

    
}
