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
    for(int i = 0; i < freq.size(); i++)
    {
        if(compress.eof())
        {
            cout << "Incorrect format" << endl;
            return -1;
        }
        else
        {
            string getFreq = "";
            getline(compress, getFreq);
            byte frequency = stoi(getFreq);
            freq[i] = frequency;
        }
    }

    HCTree ht;
    ht.build(freq);

    ofstream original;
    original.open(argv[2]);

    while(1)
    {
         unsigned char symbol = ht.decode(compress);
         if(compress.eof()){ break;}
         original << symbol;

    }

}

