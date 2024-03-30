//
//  LinkedList.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 3/4/24.
//

#include "LinkedList.hpp"


// -----------------------------------------------------
// Integer node class member definitions
// -----------------------------------------------------

Node::Node():val(0),prev(nullptr),next(nullptr){}
Node::Node(int _val, Node* _prev, Node* _next):val(_val),prev(_prev),next(_next){}
//Node::~Node(){
//    std::cout << "Node with value " << val << " is being deallocated\n";
//}


// -----------------------------------------------------
// Iterator class member definitions
// -----------------------------------------------------

Iterator::Iterator(LinkedList* _ll, Node* _n):container(_ll),curr(_n){}

int& Iterator::operator*(){
    return curr->val;
}

//Increment operator, updates iterator to next element in linked list
Iterator& Iterator::operator++(){
    curr = curr->next;
    return *this;
}

// != boolean comparison operator: returns true if both iterators are not bound to the same node in the LinkedList
bool operator!=(const Iterator& l, const Iterator& r){
    //curr stores a memory address of the node
    return (l.curr != r.curr);
}

// -----------------------------------------------------
// LinkedList class member definitions
// -----------------------------------------------------

LinkedList::LinkedList():first(new Node()),last(new Node()),size(0){
    first->next = last;
    last->prev = first;
}

Iterator LinkedList::begin(){
    return Iterator(this, this->first->next);
}

Iterator LinkedList::end(){
    return Iterator(this, this->last);
}

/*
 Insert member function
 - inserts a new node with the value int at the location to the left of the iterator
 - check iterator is bound to correct location
 - check iterator is not bound to the tail, can't insert to the left of the tail!
 */

void LinkedList::insert(Iterator it, int new_val){
    Iterator tail = Iterator(this, this->first);
    if (it != tail){
        Node* temp = new Node(new_val,it.curr->prev,it.curr);
        it.curr->prev->next = temp;
        it.curr->prev = temp;
    }
    else {
        std::cout << "Insert failed: cannot insert to the left of the tail\n";
    }
}

/*
 Parameterized constructor taking a list of integers
  - first create tail and head nodes
  - get an iterator bound to the head of the linked list
  - then using range based for loops insert elements in as nodes into LinkedList by calling insert on head iterator
 */

LinkedList::LinkedList(std::initializer_list<int> il):LinkedList::LinkedList(){
    Iterator head(this, last);
    for (int i : il){
        insert(head,i);
    }
}
/*
 Delete the node that the Iterator it is bound to
 - connect nodes to the left and righ of the current node with respect to it
 - delete node using curr pointer
 - assign curr to nullptr
 */
void LinkedList::erase(Iterator it){
    //Should have some sort of condition to check if this is the first or last node in the list, if it's equal to head or tail we should not be able to delete the dummy nodes
    it.curr->prev->next = it.curr->next;
    it.curr->next->prev = it.curr->prev;
    delete it.curr;
    it.curr = nullptr;
}

//void LinkedList::pop_back();
//void LinkedList::push_back(int);

