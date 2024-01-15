#ifndef Huffman_H
#define Huffman_H
#include"heap.h"
#include<unordered_map>
#include<bitset>
#include<map>

class HuffmanTree{    
    private:
       Node *root;
       unsigned short size;
       NodeHeap heap;
       std::unordered_map<unsigned char,std::pair<std::bitset<256>,int>> Code;
    public:
       HuffmanTree(const unsigned long long (&weight)[256]);
       ~HuffmanTree();
       void Encode(Node *&now,const int &nowlength,std::bitset<256> nowcode);
       inline const std::unordered_map<unsigned char,std::pair<std::bitset<256>,int>> &Encodemap(){
          return Code;
       }
       inline const unsigned short &GetSize() const { return size; }
       inline Node* GetRoot() const { return root; }
       void deleteallnodes(Node *node);
};

#endif