#include "HCTree.h"
//#include "HCNode.h"
#include <queue>
/**
 * Filename: HCTree.cpp
 * Author: Peter Phan
 *
 * Purpose: Implementation of a Huffman Tree that will store the path
 * leading to each character
 */


//do we need to check size?
//of freqs
void HCTree::build(const vector<int>& freqs)
{ 
    priority_queue<HCNode*> huff;
    //loop that will make a node and push them into priority queue
    for(int i = 0; i < freqs.size(); i++)
    {
    
        if(0 < freqs.at(i)){
            HCNode* node = new HCNode(freqs.at(i), i, 0, 0, 0);
            huff.push(node);       
            leaves.at(i) = node;
        }   
    }

    //constructing tree
    while(!huff.empty() && huff.size() != 1){
        HCNode* n0 = huff.top();
        huff.pop();
        HCNode* n1 = huff.top();
        huff.pop();
         
        cout << "linking nodes w/ freq " << n0->count << " and " << n1->count <<  " with 2nd symbol " << n1->symbol <<endl;
        HCNode* top = new HCNode(n0->count + n1->count, 
                      n0->symbol, 0, 0, 0);
        top->c0 = n0;
        top->c1 = n1;

        n0->p = top;
        n1->p = top;

        huff.push(top);
    }
    
    if(huff.size() == 1){
        root = huff.top();
        huff.pop();
    }

} 



void HCTree::encode(byte symbol, ofstream& out) const
{
    //std::cout << symbol <<std::endl;
    //std::cout << leaves.at(symbol)->p->symbol <<std::endl;
    HCNode* curr = leaves.at(symbol);
 
    if(!curr)
    { 
        cout << symbol << " is not inserted into the tree" << endl;
        return;}
       
    int count = 0;
    int code = 0; 
    
    //every 
    while(curr->p)
    {
        if(curr->p->c1 == curr)
        {
            code += 1 << count; 
        }

        count++;
        curr = curr->p;
    }
    
    //cout << count << " is count and " << code << " is the ht"<<endl;
    
    //case for when tree has only one node
    if(count == 0)
    {
        out << '0';
    }

 
    for(int i = count-1; 0 <= i; i--)
    {
        // out << ((code >> i) & 1);
        int bit = (code >> i) & 1;
        
        if(bit == 1){
            out << '1';
        }
        else{
            out << '0';
        }
    }

}

int HCTree::decode(ifstream& in) const
{
    HCNode* curr = root;

    if(!curr){ return 0;}

   /* if(!curr->p && !curr->c0 && !curr->c1)
    {
        return (int)curr->symbol;       
    }*/
    
     
    while(curr->c0 || curr->c1)
    {
        int read = in.get();
        //somehow write left to right
        if(in.eof()){return 0;}
        if(read == '0'){
            curr = curr->c0;
        }
        else if(read == '1'){
            curr = curr->c1;
        }
    }
    
    return (int)curr->symbol;   

}
/**
 * Helper function to destructor
 */
void HCTree::deleteAll(HCNode* n)
{
    if(!n)
        return;

    deleteAll(n->c0);
    deleteAll(n->c1);

    delete n;
}

/* Destructor */
HCTree::~HCTree(){ deleteAll(root);}
 
