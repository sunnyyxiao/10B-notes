//
//  BST.hpp
//  PIC10B
//
//  Created by Sunny Xiao on 3/15/24.
//

#ifndef BST_hpp
#define BST_hpp

#include <iostream>

class BST;

class Node{
    Node(int,std::string,Node*,Node*);
    ~Node();
    int id;
    std::string name;
    Node* left;
    Node* right;
    friend BST;
};

// It should be remarked that we implement only a elementary form of binary search tree with many key functions missing, for example removing a node, and we have not implemented iterators! This rudimentary implementation should however suffice to illustrate the power of recursion in the context of managing trees and also highlight the effectiveness of search.

class BST{
public:
    BST();
    ~BST();
    void insert(int, std::string, Node*&);
    std::string search(int, Node*);
    Node* root;
    
private:
    void destroy_tree(Node*); // used to avoid memory leaks!
};

#endif /* BST_hpp */
