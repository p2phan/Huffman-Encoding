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

    BitInputStream originalB(original);
    
    cout << "Reading file, and updating frequencies" <<endl;
    while(1)
    {
        byte count = 0;
        for(int i = 0; i < 8; i++)
        {
            int bit = originalB.readBit();
            count += bit << (7-i);
        }

 //       cout << "read " << count << " from file" <<endl; 
        //count = original.get();

        if(original.eof()){break;}
        //do I need to repeat eof or will it be repetitive
        freq.at(count)++;
    }

    cout << "Building tree" << endl;
    //builds the tree to encode
    HCTree ht;    
    ht.build(freq);

    //writes out header on output file
    cout << "Writing header" << endl;
    int bitH = 32;
    ofstream compress;
    compress.open(argv[2]);

    BitOutputStream compressB(compress);
    int distinctC = ht.getDistinctC();
    cout << "You have " << distinctC << " distinct symbols" << endl;
    for(int i = 0; i < 32; i++)
    {
        compressB.writeBit(distinctC >> (31-i));
    
    }
    
    int bits = 0;
    for(int i = 0; i < freq.size(); i++)
    {
        //cout << "before for" << endl;
        if(0 < freq[i]) { 
            int frequency = freq[i];
  //          cout << "freq is "<< frequency << endl;
            for(int j = 0; j < 32; j++)
            {
                bitH++;
                compressB.writeBit(frequency >> (31-j));
            }
    //        cout << "symbol is " << i << endl;
            for(int j = 0; j < 8; j++)
            {
                bitH++;
                compressB.writeBit(i >> (7-j));
            }
        }  
        //cout <<"after for" << endl;
    }
    original.clear();
    original.seekg(0, ios::beg);

    //int bitE = 0;
    cout << "Encoding data" << endl;
    while(1)
    {
        byte symbol = 0;
        for(int i = 0; i < 8; i++)
        {
            int bit = originalB.readBit();
            symbol += bit << (7-i);
        }
        //symbol = original.get();
        if(original.eof()){break;}
//        cout <<  " encoding " << symbol <<endl;;
        ht.encode(symbol, compressB);
        //bitE++;
    }
    compressB.flush();
    //:w
    //cout<< bitE << " endcoded" << endl;   
    original.close();
    compress.close();     

/*     ifstream compress;
    compress.open(argv[1]);

    if(!compress.is_open()){
        cout << "Failed to open " << argv[1] << endl;
        return -1;
    }
    
    BitInputStream compressB(compress);

    ofstream originalBIT;
    originalBIT.open(argv[2]);

    BitOutputStream originalB(originalBIT);
    
while(1){
        int symbol = 0;
        for(int i = 0; i < 8; i++)
        {
            int bit = compressB.readBit();
            //cout << bit << endl;
            symbol |= (bit << (7-i));
                 
        }
            //cout << "read" << symbol  <<endl;

        if(compress.eof()){
        break;
        }
        
        for(int i = 0; i< 8; i++){
            //cout <<( (symbol >>(7-i))&1) << endl;
            originalB.writeBit(symbol >> (7-i));


        }
            //cout << "write" << endl;
    }
    originalB.flush();
*/
}
