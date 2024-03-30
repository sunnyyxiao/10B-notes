//
//  LinkedList.hpp
//  PIC10B
//
//  Created by Sunny Xiao on 3/4/24.
//

#ifndef LinkedList_hpp
#define LinkedList_hpp

#include <iostream>
// Simple integer node
class Node{
public:
    Node();
    Node(int _val, Node* _prev, Node* _next);
    ~Node(){
//        std::cout << "Node with value " << val << " is being deallocated\n";
    }
    int val;
    Node* prev;
    Node* next;
    //following allows us to access private members of Iterator and LinkedList inside node
    friend class Iterator;
    friend class LinkedList;
};

//We have to declare in advance as Iterator class takes pointers to Linked List class objects as parameters. We define it later...
class LinkedList;

// Iterator class
class Iterator{
public:
    Iterator(LinkedList*, Node*);
    int& operator*();
    Iterator& operator++();
    friend class LinkedList;
    friend bool operator!=(const Iterator&, const Iterator&);
private:
    const LinkedList* const container;
    Node* curr;
};

// LinkedList Class for ints
class LinkedList{
public:
    LinkedList();
    LinkedList(std::initializer_list<int> il);
    //returns pointer bound to the one after the 'tail node'
    Iterator begin();
    //returns pointer bound to 'head node'
    Iterator end();
//    void pop_back();
//    void push_back(int);
    void insert(Iterator it, int new_val);
    void erase(Iterator);
private:
    Node* first;
    Node* last;
    size_t size;
};


#endif /* LinkedList_hpp */
