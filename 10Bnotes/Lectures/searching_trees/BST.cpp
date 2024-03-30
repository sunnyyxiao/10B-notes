//
//  BST.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 3/15/24.
//

#include "BST.hpp"


// -----------------------------------------------------
// Integer node class member definitions
// -----------------------------------------------------
Node::Node(int _id, std::string _name, Node* _left, Node* _right):
    id(_id), name(_name), left(_left), right(_right){}
Node::~Node(){
    std::cout << "Deleting node with value " << id << ", name " << name << "\n";
}

// -----------------------------------------------------
// BST class member definitions
// -----------------------------------------------------

//Default constructor creates a tree with no nodes, so root just is bound to nullptr
BST::BST():root(nullptr){}


//Destructor
BST::~BST(){
    destroy_tree(root);
}


/*
    - If tree is empty then bind root to a new node and set both its left and right pointers to nullptr
    - Othwerwise check new_val against the current node value
        - if it is smaller then call insert on the left
        - if it is larger then call insert on the right
        - if it is equal to then say not inserting as entry already exists
 */
void BST::insert(int new_id, std::string name, Node*& p){
    if (p == nullptr){
        p = new Node(new_id,name,nullptr,nullptr);
    }
    else {
        if (new_id == p->id){
            std::cout << "Node with id = " << new_id << " already present in tree, insertion failed\n";
        } else if (new_id > p->id){
            insert(new_id,name,p->right);
        } else {
            insert(new_id,name,p->left);
        }
    }
}

/*
 Search member function:
    - if p is nullptr then we have reached beyond leaves and so is not value is not present in tree
    - else
        - if value at current node is equal to r then return name
        - else if value is smaller than id of current node search the left hand branch
        - else search the right hand branch
 */

std::string BST::search(int t, Node* p){
    if (p == nullptr){
        std::cout << "ID not present in tree, returning 0\n";
        return "0";
    } else {
        if (t == p->id){
            return p->name;
        } else if (t > p->id){
            return search(t,p->right);
        } else {
            return search(t,p->left);
        }
    }
}

/*
 Delete tree member function:
    - if p is not nullptr
        - call destroy on right hand branch
        - call destroy on left hand branch
        - delete current node
 */


void BST::destroy_tree(Node* p){
    if (p == nullptr){
        return;
    } else {
        destroy_tree(p->right);
        destroy_tree(p->left);
        delete p;
        return;
    }
}
