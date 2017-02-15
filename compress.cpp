#include "HCTree.h"
#include<iostream>
#include<fstream>

/**
 * Filename: compress.cpp
 * Author: Peter Phan
 * Purpose: To compress files using huffman implementation 
 *
 */


int main(int argc, char* argv[]){
    

    if(argc != 3){
        cout << "Invalid number of arguments\n"
             << "Usage ./compress <file to be compressed> <output file>\n"; 
        return -1;
    }

    ifstream original;
    original.open(argv[1]);

    if(!original.is_open()){
        cout << "Failed to open " << argv[1] << endl;
        return -1;
    }

    vector<int> freq(256, 0);
    while(1)
    {
        byte count = original.get();
        if(original.eof()){ break;}
        freq.at(count)++;
    }
    
    HCTree ht;
    ht.build(freq);
    original.clear();
    original.seekg(0, ios::beg);

    ofstream compress;
    compress.open(argv[2]);   
    while(1)
    {
        byte symbol = original.get();
        if(original.eof()){ break;}
        ht.encode(symbol, compress);
    }
   
    original.close(); 
    compress.close();

    
}
