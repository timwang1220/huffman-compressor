#include"huffman.h"
#include<stack>

#include<iostream>


HuffmanTree::HuffmanTree(const unsigned long long (&weight)[256]){
    size=0;
    for (int i=0;i<256;i++){
       if (weight[i]) {heap.push(new Node(i,weight[i]));  size++;}
    }
    if (size==0) {root=nullptr; return;}
    while (!heap.empty()){
       Node *l1=heap.top();
       heap.pop();
       if (heap.empty()) { root=l1; break;}
       Node *l2=heap.top();
       heap.pop();
       Node *merged=new Node(-1,l1->val+l2->val,l1,l2);
       heap.push(merged);
    }
    Encode(root,0,0);
}
void HuffmanTree::deleteallnodes(Node *node){
    if (node==nullptr) return;
    deleteallnodes(node->left);
    deleteallnodes(node->right);
    delete(node);
}
HuffmanTree::~HuffmanTree(){
    deleteallnodes(root);
}

void HuffmanTree::Encode(Node *&now,const int &nowlength,std::bitset<256> nowcode){
    if (now->c!=-1) Code[now->c]=std::pair<std::bitset<256>,int>(nowcode,nowlength);
    if (now->left!=nullptr) Encode(now->left,nowlength+1,nowcode);
    nowcode[nowlength]=1;
    if (now->right!=nullptr) Encode(now->right,nowlength+1,nowcode);
}