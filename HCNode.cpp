#include "HCNode.h"

/**
 * Filename: HCNode.cpp
 * Edited by Peter Phan A13042904 cs100wdh
 *
 * Purpose: This class will be used as nodes for a Huffman tree
 */

/** Less-than comparison, so HCNodes will work in std::priority_queue
 *  We want small counts to have high priority.
 *  And we want to break ties deterministically.
 *
 *  Parameter:
 *         other: the HC node we are comparing current HC Node to
 */
bool HCNode::operator<(const HCNode& other)
{
    //return the opposite because we want the lowest freq 
    //to be at the top
    if(count != other.count) 
    { 
        return other.count < count;
    }
    
    //when freq are the same, the symbol with larger ASCII value
    //will have priority
    return symbol < other.symbol;
}  
