#include "util.h"
#include "DictionaryTrie.h"
/**
 * File: DictionaryTrie.cpp
 * Purpose: lets user store words in TST implementation
 * Also, allows users to find top number of words with 
 * the same prefix.
 *
 * Authors: Christine Alvardo and WI2017 Tutors
 * Peter Phan A1342904 cs100wdh
 *
 */


/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){ root=nullptr;}

/** Helper function for insert and find that will traverse the tree 
 *  until either the node matches the letter or everything else is null
 *
 *  Return the node with either the same char or the node in which 
 *  it's supposed to go
 *  
 *  Parameters:
 *        get: this is the node to search through
 *        c: this is the char that we are looking through
 *        the nodes for
 *     
 */
TrieNode* DictionaryTrie::traverseTrie(TrieNode* get, char c) const
{
  
  
  TrieNode* curr = get;
  // We check condition of mid because we don't want to step in yet
  //  while(curr->mid){
  while(curr->right || curr-> left){

    TrieNode* temp = curr;

    //if and else if updates based on comparision to c
    if(c < curr->letter){
       curr = curr->left;
    }

    else if( curr->letter < c){
      curr = curr->right;
    }

    // If the data is equal to c we are at the node we want
    // and we return it
    else {
      return curr;
    }
    
    // When updating makes curr null we will go back    
    if(!curr){
      curr = temp;
      break;
    }
  }

  //if we reach node with no mid but

  
  //we are at the node we want so we return it
  return curr;
}


/**
 * Helper fuction for find and predictNumCompletions that will find 
 * node in tree
 *  
 * Parameter:
 *           word: string to look in trie for
 */
TrieNode* DictionaryTrie::getNode(std::string word) const {

  //we will let user deal with null nodes
  if(!root)
  {
    return root;
  }

  //traverse through the tree
  TrieNode* curr = root;
  char c;

  //traverse through the tree for each letter in the string
  for(unsigned int i = 0; i < word.length() ; i++)
  {

    c = word[i];

    //check to see if c is valid
    if(c < 'a' || 'z' < c){
      if( c != ' '){
        std::cout << "Invalid Input. Please retry with correct input" <<
                std::endl;
        return NULL;
      }
    } 

 
    // traversal either returns node with same letter
    // or a null pointer
    TrieNode* check = traverseTrie(curr, c);

    //check if node is supposed to go left or right
    if(c < check->letter) {
      curr = check->left;
    }
   
    else if (check->letter < c) {
      curr = check->right;    
    }

    // Checks if we reached the end of our word first
    // otherwise it updates
    else {
      if(i == word.length()-1) {
        curr = check;
        break;
      }
      else {
        curr = check->mid;
      }
    }
 
    // If curr is null at all then it will return false
    // Otherwise, there will be a seg fault
    if(!curr){return curr;}
  } 
 
  //if we past the for loop that's the node we want to return
  return curr;

}


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

TrieNode* DictionaryTrie::addNode(std::string word, unsigned int i,
                                  unsigned int freq){
  char c = word[i];
  // This is the begging of our Node chain
  TrieNode* begin = new TrieNode(c);
  // We have another node reference cuz we want to return 
  // the beginnig of Node
  TrieNode* add = begin;
  // Increments i to avoid duplicates
  i++;

  for( ;i<word.length(); i++){
    
    // After every node is made, we put that as mid Node
    // and update add Node to new Node
    c = word[i];
    add->mid = new TrieNode(c);
    add = add->mid;
  }
 
  // We want the update at the end 
  add->freq = freq;
  add->isWord = true;
  return begin;
  

}


/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) 
 * 
 * Paramters:
 *     word: string to insert
 *     freq: freq of that string
 *
 */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
  // null case of root, creates the trie
  if(root==NULL){
    root = addNode(word, 0, freq); 
    return true; 
  }

  //curr to traverse through the trie
  TrieNode* curr = root;
  char c;

  //traverse through the tree for each letter until it reaches 
  //dead end or the node of the last letter
  for(unsigned int i = 0; i<word.length(); i++ ) {

    c =  word[i]; 

    //check to see if c is valid
    if(c < 'a' || 'z' < c){
      if( c != ' '){
        std::cout << "Invalid Input. Please retry with correct input" <<
                std::endl;
        return false;
      }
    } 

    // Traversal will either return node that in which 
    // the node's data is equal to the current c
    // Or it will return the last node in which we 
    // add nodes left or right 
    TrieNode* check = traverseTrie(curr, c);

    // For if and else if conditions, we check the node
    // we want to go to, if it's null we create a chain
    // and add it to that spot
    // if not we go to that spot
    if(c < check->letter){
      if(check->left){
        curr = check->left;
      }
      else{
        check->left = addNode( word, i, freq);
        return true; 
      }
    }

    else if(check->letter < c) {
      if(check->right){
        curr = check->right;
      }
      else {
        check->right = addNode(word, i, freq);
        return true;
      }


    }

    // If the one we want to go is the mid Node
    // We check to see if we reached the end 
    // Otherwise, we have a null check
    else {
      if(i == word.length()-1) {
        curr = check;
        break;
      }
      else if(check->mid){
        curr = check->mid;
      }
      else{
        // we start at i+1 be the one check is on already
        // is the same letter as word[i]
        check->mid = addNode( word, i+1, freq); 
        return true;
      }
    }
  } 

  // We have gone through every node and now
  // we are at the last node
   
  if(curr->isWord){
    // is there is already a word we will update to larger freq
    if( curr->freq < freq) {curr->freq = freq;}
    return false;
  }
  //otherwise we update the node
  else{
    curr->isWord = true;
    curr->freq = freq; 
  }

   
  return true;
}


/* Return true if word is in the dictionary, and false otherwise 
 * Parameters:
 *     word: string to find, this is const so we don't
 *     accidently mess up the string while searching
 */
bool DictionaryTrie::find(std::string word) const
{
  TrieNode* search = getNode(word);
 
  //null check  
  if(!search)
  {
    return false;
  }

  // After we end up at the node with the last letter of the 
  // word, the bool in that node will tell us if it is a word or not
  return search->isWord;
}


/**
 *  Recursive function to help add find words and add them into vector
 *
 *  Parameters:
 *             top: set of pairs to store freq and the current word
 *             check: current node we are checking
 *             word:  current word
 *             num_completions: number of words to return
 */
void DictionaryTrie::getWords( 
          std::set<std::pair<unsigned int, std::string>>* top, 
          TrieNode* check, std::string word, 
          unsigned int num_completions)
{
  //null check
  if(!check) {return;}
 
  //if the node is word, we add that into top
  if(check->isWord){

    //case when the size of top is already at num_completions
    if(num_completions <= top->size()) {
      std::set<std::pair<unsigned int, std::string>>::iterator it = 
                               top->begin();
      //if lowest frequency in set is lower than current node's freq
      //we delete that and insert pair of freq and word

      if((*it).first < check->freq) {
        top->erase(it);
        top->insert(
            std::pair<unsigned int, std::string>(check->freq, 
            word+check->letter));

      }
    }
   
     
    //current node might be skip node so when we confirm that 
    //it's a word, we add letter of current node
    else {
      top->insert(
            std::pair<unsigned int, std::string>(check->freq, 
            (word+check->letter)));
    }
  }


  //recursive DFS of the TST
  getWords(top, check->left, word, num_completions);
  //only the middle node will consider it's parent as part of word
  //hence word + check->letter
  getWords(top, check->mid, word + check->letter, num_completions);       
  getWords(top, check->right, word, num_completions);       
  
  return;

}

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
 *
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
  //empty vector of strings
  std::vector<std::string> topWords;

  if(prefix == ""){
    return topWords;
  }
 
  //find the node with the same letter as the last one in prefix
  TrieNode* pre = getNode(prefix);

  //if we don't find prefix then there are no words in the tree
  if(!pre){ return topWords; }
  
  std::set<std::pair<unsigned int, std::string>> top; 


  //checks if curr is word then the mid child will be passed 
  //into recursive function
  if(pre->isWord){
    top.insert(
           std::pair<unsigned int, std::string>(pre->freq, prefix));
  }

  getWords(&top, pre->mid, prefix, num_completions);

  //puts in words in order from highest to lowest freq
  auto it = top.rbegin();
  for( ; it != top.rend(); it++){
    topWords.push_back((*it).second);
  } 
  
  return topWords;
}
 
/** This is a helper function to the destructor
 *  
 *  Parameter: 
 *      n: this is the root of the trie in which we will
 *      delete all nodes
 *
 *
 *  We will do a recursive post-order traversal 
 *  and this will free all memory
 */
void DictionaryTrie::deleteAll(TrieNode* n)
{
  //base case of recursion 
  if(!n){ return; }
  
  // Recursively visits bottom nodes,
  // and deletes it's way upwards to root
  deleteAll(n->left);
  deleteAll(n->mid);
  deleteAll(n->right);

  delete n;

}
/* Destructor */
DictionaryTrie::~DictionaryTrie(){ deleteAll(root);}



