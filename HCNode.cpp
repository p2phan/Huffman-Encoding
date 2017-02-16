#include "HCNode.h"

/**
 * Filename: HCNode.cpp
 * Author: Peter Phan A13042904 cs100wdh
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
    if(count != other.count) 
    { 
        return count < other.count;
    }
    
    return symbol < other.symbol;
}  
