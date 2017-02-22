#include "HCTree.h"
#include "HCNode.h"
#include <queue>
/**
 * Filename: HCTree.cpp
 * Author: Peter Phan
 *
 * Purpose: Implementation of a Huffman Tree that will store the path
 * leading to each character
 */

/** Returns number of Distinct bits in a file
 */
int HCTree::getDistinctC()
{
    return distinctC;
}

/**
 * Creates a huffman tree based on the freq of each unsigned char
 *
 * Parameters:
 *            freqs: vector containing the freq at the index of
 *            a character's ASCII value
 */
void HCTree::build(const vector<int>& freqs)
{ 
    //creates prioity queue whose comparison makes it s.t the high
    //comparison get most prioirty
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> huff;

    //loop that will make a node containing freq
    //and push them into priority queue
    for(int i = 0; i < freqs.size(); i++)
    {
        //we don't care about char w/ 0 freq
        if(0 < freqs.at(i)){
            HCNode* node = new HCNode(freqs.at(i), i, 0, 0, 0);
            huff.push(node);       
            leaves.at(i) = node;
            distinctC++;
        }   
    }

    //constructing tree
    while(!huff.empty() && huff.size() != 1){
        //gets top 2 nodes and creates another one that combines freq
        HCNode* n0 = huff.top();
        huff.pop();
        HCNode* n1 = huff.top();
        huff.pop();
         
        HCNode* top = new HCNode(n0->count + n1->count, 
                      n0->symbol, 0, 0, 0);
        //updating pointer
        top->c0 = n0;
        top->c1 = n1;

        n0->p = top;
        n1->p = top;
    
        //push back new node to compare with the rest
        huff.push(top);
    }
    
    //condition where huffman tree only has one node   
    if(huff.size() == 1){
        root = huff.top();
        huff.pop();
    }

} 

void HCTree::encode(byte symbol, BitOutputStream& out) const
{
    HCNode* curr = leaves.at(symbol);

    if(!curr) { return;}

    //repetitive?
    if(!curr->p && !curr->c0 && !curr->c1)
    {
         out.writeBit(0);
    }

    while(curr->p)
    {
        if(curr->p->c1 == curr)
        {
            out.writeBit(1);
        }
        
        else
        {
            out.writeBit(0);
        }
        
        curr = curr->p;

    }


} 


/**
 * Encodes a byte and writes it out to file
 *
 * Parameters:
 *            symbol: the byte to encode using 
 *            huffman tree
 *
 *            out: the ofstream to write the result 
 *            of the encoded symbol
 */
void HCTree::encode(byte symbol, ofstream& out) const
{
    HCNode* curr = leaves.at(symbol);
 
    //null check
    if(!curr)
    { 
        cout << symbol << " was not inserted into the tree" << endl;
        return;}
       
    int count = 0;
    int code = 0; 
    
    //traverses up the tree and at every step it will put
    //the bit according to the edge with to the correct place
    while(curr->p)
    {
        if(curr->p->c1 == curr)
        {
            code += 1 << count; 
        }

        count++;
        curr = curr->p;
    }
    
    
    //case for when tree has only one node
    if(count == 0)
    {
        out << '0';
    }

 
    //writes out the bits from left to write to the stream
    for(int i = count-1; 0 <= i; i--)
    {
        int bit = (code >> i) & 1;
        
        if(bit == 1){
            out << '1';
        }
        else{
            out << '0';
        }
    }

}


int HCTree::decode(BitInputStream& in) const
{

    HCNode* curr = root;
    
    if(!curr){return 0;}

    while(curr->c0 || curr->c1)
    {
        int bit = in.readBit();
        
        if(bit == 1)
        {
            cout << "1" << endl;
            curr = curr->c1;
        }

        else
        {
            cout << "0" << endl; 
            curr =  curr->c0;
        }
    }
    
    return (int)curr->symbol;

}


/**
 * Decodes from the stream and returns the result
 *
 * Parameter:
 *           in: the ifstream to read from and decode
 */
int HCTree::decode(ifstream& in) const
{
    HCNode* curr = root;

    //null check
    if(!curr){ return 0;}

    //traverse through the huffman tree until it reaches a dead end
    while(curr->c0 || curr->c1)
    {
        int read = in.get();

        //stops the decoding if the reach end of file early
        if(in.eof()){return 0;}

        //moves the through the node's children
        if(read == '0'){
            curr = curr->c0;
        }
        else if(read == '1'){
            curr = curr->c1;
        }
    }
    
    //we return the symbol at the node which will be the decoded byte
    return (int)curr->symbol;   

}
/**
 * Helper function to destructor
 */
void HCTree::deleteAll(HCNode* n)
{
    if(!n)
        return;
    
    //recursive post-order traversal
    deleteAll(n->c0);
    deleteAll(n->c1);

    delete n;
}

/* Destructor */
HCTree::~HCTree(){ deleteAll(root);}
 
