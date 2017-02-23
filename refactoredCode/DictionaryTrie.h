/**
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 *  Edited by Peter Phan A13042904 cs100wdh
 */

#ifndef DICTIONARY_TRIE_H
#define DICTIONARY_TRIE_H

#include <vector>
#include <queue>
#include <set>
#include <string>

/**
 * The class for a Node of a TST. It will store
 * letters, if that node is a word and the frequency of that word
 *
 */
class TrieNode;

/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class DictionaryTrie
{
public:

  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) 
   * 
   * Paremters:
   *     word: string to insert
   *     freq: freq of that string
   *
   * */
  bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise 
   * 
   * Parameters:
   *     word: string to find, this is const so we don't
   *     accidently mess up the string while searching
   * */
  bool find(std::string word) const;

  /* Return up to num_completions of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than num_completions legal completions, this
   * function returns a vector with as many completions as possible.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the num_completions most frequent completions
   * of the prefix)
   *
   * Parameters: 
   *            prefix: start of the word to find words in subtree
   *            num_completetions: number of words with highest frequncies
   *            to return
   */
  std::vector<std::string>
  predictCompletions(std::string prefix, unsigned int num_completions);

  /* Destructor */
  ~DictionaryTrie();

private:
  // Add your own data members and methods here

  /*This will be the root of the ternary tree*/
  TrieNode* root;

  /** Helper function for insert and find 
   *  that will traverse the tree until either the node 
   *  matches the letter or everything else is null
   *  
   *
   *  Return the node with either the same char
   *  or the node in which it's supposed to go 
   *  left or right but they are null
   *
   *  Parameters:
   *      get: this is the node to search through
   *      c: this is the char that we are looking through
   *      the nodes for
   *
   */
  TrieNode* traverseTrie(TrieNode* get, char c) const;

  /** Helper function for insert 
   *  
   *  Returns the beginning of added subtrie
   *
   *  Parameter:
   *      word: word to made nodes out of
   *      i: position from which to start makin a node chain
   *      freq: frequency to update end of chain
   *
   *  Effect: returns a chain of Nodes from char of the string
   *  from i to the end 
   */ 
  TrieNode* addNode(std::string word, unsigned int i, unsigned int freq);


  /**
   * Helper fuction for find and predictNumCompletions that will find 
   * node in tree
   *  
   * Parameter:
   *           word: string to look in trie for
   */
  TrieNode* getNode(std::string word) const;

  /**
   *  Recursive function to help add find words and add into vector
   *
   *  Parameters:
   *             top: set of pairs to store freq and the current word
   *             check: current node we are checking
   *             word:  current word
   *             num_completions: number of words to return
   */
  void getWords(std::set<std::pair<unsigned int, std::string>>* top, 
           TrieNode* check, std::string word, 
           unsigned int num_completions);
  
  /** This is a helper function to the desctructor
   *  
   *  Parameter: 
   *      n: this is the root of the trie in which we will
   *      delete all nodes
   *
   *
   *  We will do a post-order traversal and this will free all memory
   *
   */ 
  static void deleteAll(TrieNode* n);
};

class TrieNode
{
public:

  /** default constructor
   *  Mid, left and right pointer are default to nullptr
   *  Each node is is set to not a word
   *  Freq is 0
   */
  TrieNode(const char c) : mid(nullptr), left(nullptr),
                           right(nullptr), letter(c),
                           isWord(false), freq(0){}
   
  //the three nodes are part of the structure of the ternary search tree
  /* Middle Node contains next letter of the word  */
  TrieNode* mid; 

  /* contains Node holding letter that is smaller than our letter */
  TrieNode* left;

  /* contains Node holding letter that is bigger than our letter */
  TrieNode* right;  

  /* holds letter in a word */
  char const letter; 

  /* Node containing last letter of word stored is true
   * Default is false
   */
  bool isWord; 

  /* Hold frequency of a word, 
   * Like isWord, should be stored in Node that holds last letter
   * of the word
   * Default is 0
   */
  unsigned int freq;
};


#endif // DICTIONARY_TRIE_H
