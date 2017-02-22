#include "HCTree.h"
#include<iostream>
#include<fstream>

/**
 * Filename uncompress.cpp
 * Author: Peter Phan cs100wdh A13042904
 * Purpose: to uncompress file using huffman implementation
 *
 */

int main(int argc, char* argv[])
{
    if(argc != 3){
        cout << "Invalid number of arguments\n"
             << "Usage ./uncompress <file to be uncompressed> <output file>\n";
        return -1;
    }

    ifstream compress;
    compress.open(argv[1]);

    if(!compress.is_open()){
        cout << "Failed to open " << argv[1] << endl;
        return -1;
    }

    vector<int> freq(256, 0);
    
    /*
    int count = 0; 
    for(int i = 0; i < freq.size(); i++)
    {
        string getFreq = "";
        getline(compress, getFreq);
        if(compress.eof())
        {
            cout << "Incorrect format" << endl;
            return -1;
        }
        else
        {
           int frequency = stoi(getFreq);
           // cout << frequency << endl;
            freq[i] = frequency;
          //  cout << frequency << endl;
            count += frequency;
        }
    }

    HCTree ht;
    ht.build(freq);

    ofstream original;
    original.open(argv[2]);

    for( ; 0 < count ; count--)
    {
        unsigned char symbol = ht.decode(compress);
        //cout << compress.eof() << " for " << count++ <<endl;
        if(compress.eof()){ break;}
        original << symbol;

    }
    compress.close();
    original.close();
    */
    

    compress.get();
  
    cout << "distinct C" << endl; 
    BitInputStream compressB(compress);   
    int distinctC = 0;
    for(int i = 0; i < 32; i++)
    {
        //cout << "reading distinctC" << endl;
        int bit = compressB.readBit();
        distinctC += bit << (31-i);
    }
 
    int count = 0;

        cout << distinctC << " is distinct C" <<endl;
    for(int i = 0; i < distinctC; i++)
    {
        //cout << "reading freq/sym" << endl;
        int frequency, symbol = 0;
        for(int j = 0; j < 32; j++)
        {
            frequency += compressB.readBit() << (31-j);
        }
        
        for(int j = 0; j < 8; j++)
        {
            symbol += compressB.readBit() << (7-j);
        }
        cout << frequency << " is frequency of " << symbol << endl;
        freq[symbol] = frequency;
        count += frequency;

    }
 
    HCTree ht;
    ht.build(freq);
    
    ofstream original;
    original.open(argv[2]);    
    
    BitOutputStream originalB(original);

    for( ; 0 < count; count--)
    {
        cout << " in for to decode" << endl;
        unsigned char symbol = ht.decode(compressB);
        if(compress.eof()){ break;}
        cout << symbol << " written to the file" << endl;
        //original << symbol;
        for(int i = 0; i < 8; i++)
        {    originalB.writeBit(symbol >> (7-i));}
    }

    compress.close();
    original.close();   
///read int, that the number of distinct C
//read and store nodes until0
//build tree
//
}

