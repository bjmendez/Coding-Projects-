
#ifndef HW5_RHYMEBOT_H
#define HW5_RHYMEBOT_H
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <utility>
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <iterator>
#include <string>
#include <cctype>
#include <string.h>

using namespace std;

//TrieNode class for the Nodes in the Trie
class TrieNode {
public:
    
  TrieNode() {
    //Node for every letter of the alphabet     
    for (int i=0;i<26;i++){
        child[i] = NULL;
    }
  }
    
    TrieNode* child[26];
    string isString;
    bool isWord;
    //int value;
};


//Trie made up TrienODES
class Trie {
public:
    Trie() {
        root = new TrieNode();
        
    }
 
    //Insert method for putting a a word based on its prounaction into the Trie and the actual word. 
    // I.E string s would be K AH0 M P Y UW1 T ER0 and the word would be COMPUTER  
    // Marking the leaf as being the end of the word and holding the actual word 	
    void insert(string s,string word) {
        TrieNode *node = root;
        int length = s.size();
       
        for (int i=0;i<length;i++){

        	
            
            int index = s[i] - 'a';
           	

            if (! node->child[index]){
                node->child[index] = new TrieNode();
                 
                
            }
            node = node->child[index];
        }
        
        //count++;
        //node->value= count;
        node->isWord = true;
        node->isString = word;
    }
    
    //Method for finding the top matching strings starting from a node 
    void findStrings(TrieNode *node,int top){
    	
    	
    	if (node->isWord){
         	
    		ans = node->isString;
        if(ans != ""){
    		cout << ans << endl;
    		node->isWord = false;
    		y++;
    		}
    	}

    	for (int i =0; i<26; i++){
        if(y==top){
          break;
        }
    		
    		if(node->child[i] == 0){

    			continue;
    		}
    		

    		findStrings(node->child[i],top);
    		
    	}
    	
    }

    /*void findTop(TrieNode *node){
    	for(int i =0; i <26; i++){
   			if (node->child[i] == 0){
       			continue;
       		}	
       				
       		findStrings(node->child[i]);
       		cout << ans << endl;
       		x++;
       	}			
    }*/
    //Method for finding all words 
    void allwords(){
      TrieNode *node = root;
      findStrings(root,1000000);
      //cout << y <<endl;
    }
    //Method for finding rhymthing words
    // Prefix is the word we want to rhyme with and top is the integer of how many rhymes we are trying to find for that word 
    void startsWith(string prefix,int top) {
        TrieNode *node = root;
        
        
        
        int length = prefix.size();
        for (int i=0;i<length;i++){
       		 	
            

            int index = prefix[i] - 'a';
            
            if (node->child[index]){
                node = node->child[index];
                
                count++;
                previousnodes.push_back(node);


            }
            else{
            	while (top != y){
       				findStrings(node,top);
              if(top != y){
                count--;
                node = previousnodes[count];
              }
       			  else{
                break;
              }
            	}
            	length = 0;
            }
            
        }
         
      
       	
       	
        
    }
 
private:
    TrieNode* root;
    string ans;
    int count = -1;
    int x = 0;
    int y = 0;
    vector<TrieNode*> previousnodes;
};


//Class that implements the Trie and TrieNodes and will handle the rhyming and parsing of files 
class RhymeBot {
private:
	
  Trie* trie = new Trie();


public:

	RhymeBot();
	RhymeBot(int argc, char *argv[]);
	unordered_map<string, string> parseDictionary(char *argv[1]);
	void parsePhrases(char *argv[2]);
  void Loadfromfile(char c);
	void TopRhyme(char *argv[]);



};


#endif //HW5_RHYMEBOT_H
