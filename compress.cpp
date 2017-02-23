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

    if(argv[1] == argv[2]){
        cout << "Please enter different text files for input and output files"
             << endl;
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

    //for use without BitInput/OutputStream
    /*
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
    */
  
    //read bits at a time from the file
    BitInputStream originalB(original);
    
    int bytes = 0; //counts the number of bytes in the file
    cout << "Reading file, and updating frequencies" <<endl;
    while(1)
    {
        byte count = 0;
        for(int i = 0; i < 8; i++)
        {
            int bit = originalB.readBit();
            count += bit << (7-i);
        }
        
        //eof check
        if(original.eof()){break;}

        freq.at(count)++;
        bytes++;
    }

    cout << "Building tree" << endl;
    //builds the tree to encode
    HCTree ht;    
    ht.build(freq);

    //writes out header on output file
    cout << "Writing header" << endl;
    ofstream compress;
    compress.open(argv[2]);

    //writes bits at a time
    BitOutputStream compressB(compress);


    int distinctC = ht.getDistinctC();
    cout << "You have " << distinctC << " distinct symbols" 
         << " and " << bytes << " number of bytes" << endl;

    //for header, writes the frequency
    for(int i = 0; i < 32; i++)
    {
        compressB.writeBit(distinctC >> (31-i));
    
    }
    
    //writes out the freq, and symbol
    //freq takes 32 bits
    //symbol takes 8 nits;
    int bits = 0;
    for(int i = 0; i < freq.size(); i++)
    {
    
        if(0 < freq[i]) { 
            int frequency = freq[i];
    
            for(int j = 0; j < 32; j++)
            {
                compressB.writeBit(frequency >> (31-j));
            }
    
            for(int j = 0; j < 8; j++)
            {
                compressB.writeBit(i >> (7-j));
            }
    
        }  
        //cout <<"after for" << endl;
    }
    
    //resets to read from top of file
    original.clear();
    original.seekg(0, ios::beg);

    cout << "Encoding data" << endl;
    
    while(1)
    {
        byte symbol = 0;
        for(int i = 0; i < 8; i++)
        {
            int bit = originalB.readBit();
            symbol += bit << (7-i);
        }
        if(original.eof()){break;}
        ht.encode(symbol, compressB);
    }

    //puts last bits onto files
    compressB.flush();
    original.close();
    compress.close();     

}
