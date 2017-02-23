#include "HCTree.h"
#include<iostream>
#include<fstream>
#include<bitset>

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
    //<< endl;
  
    //cout << "distinct C" << endl; 
    BitInputStream compressB(compress);   

    cout << "Reading header from file " << (argv[1]) << endl; 
    int distinctC = 0;
    for(int i = 0; i < 32; i++)
    {
        //cout << "reading distinctC" << endl;
        int bit = compressB.readBit();
        distinctC |= bit << (31-i);
    }
 
    unsigned int count = 0;

    cout << "There are " << distinctC << " distinct characters" << endl;
    for(int i = 0; i < distinctC; i++)
    {
        //cout << "reading freq/sym" << endl;
        int frequency = 0; 
        int symbol = 0;
        int bit = 0;
        for(int j = 0; j < 32; j++)
        {
            bit = compressB.readBit();
            frequency |= bit << (31-j);
            bitset<8> frequencyB(frequency);
            //cout << bit << "is bit" <<endl;
        }
        
        for(int j = 0; j < 8; j++)
        {
            symbol |= compressB.readBit() << (7-j);
        }
        //cout << frequency << " is frequency of " << symbol << endl;
        freq[symbol] = frequency;
        count += frequency;

    }
    cout << " ... and size " << count << " bytes" << endl; 
 

    cout << "Building huffman tree..." << endl;
    HCTree ht;
    ht.build(freq);
    
    ofstream original;
    original.open(argv[2]);    
    
    BitOutputStream originalB(original);

    cout << "Decoding file to " << (argv[2]) << endl;

    for( ; 0 < count; count--)
    {
        unsigned char symbol = ht.decode(compressB);
        //if(compress.eof()){ break;}
 //      cout << symbol << " written to the file" << endl;
        //original << symbol;
        for(int i = 0; i < 8; i++)
        {    
            originalB.writeBit(symbol >> (7-i));
        }
    }

    compress.close();
    original.close();   
}

