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

}

