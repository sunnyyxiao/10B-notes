//
//  linked_lists.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 3/4/24.
//

#include <iostream>
#include <initializer_list>
#include <vector>
#include "LinkedList.hpp"

/*
 Agenda:
 - Motivation for iterators: range based for loops
 - Overview of iterators:
    - Enable iteration over containers which are not necessarily stored contiguously
    - Essentially wrappers for pointers to elements of a container with useful/natural operator overloads
 - Implement a node class
 - Implement an iterator class
 - Implement LinkedList class
 */

int main(){
    {
        /*
         Range based for loops
         Iterators are like pointers, but often have less functionality.
         A good motivation for iterators is that they enable range-based for loops, so let's talk about range-based for loops.
         
         Here's a common example...
         */
        std::cout << "RANGE BASED FOR LOOPS:\n";
        std::vector<int> v {1,2,3,4,5,6,7,8};
        std::cout << "Range based for loop\n";
        
        
        /*
         Generic syntax
         for ([const] type [&] element : container){
            loop body
         }
         
         The type should be the same as the elements of the container (**). [const] and [&] indicate that 'const' and '&' are optional.
         
         The range-based for loop is an abbreviation for the following code (*).
         
         {
            auto end = container.end();
         
            for (auto it = container.begin(); it!= end; ++it){
                [const] type [&] element = *it;
            
                loop body
            }
         }
         The 'auto' keyword is used for declarations. It automatically detects the return type of the right-hand side of the initializing expression.
         
         In the case of the example, we obtain the folowing equivalent code.
         */
        std::cout << "Simulated range based for loop:\n";
        auto end = v.end();
        for (auto it = v.begin(); it != end; ++it) {
            int val = *it;
            std::cout << val << ' ';
        }
    }
    
    {
        /*
         ITERATORS
         Now that we've seen how a range-based for loop is executed, there are some natural questions:
          - what's the type of 'it', v.begin(), and v.end()?
          - why can we use operator!=, operator++, and operator*?
        */

        // For a std::vector<int>, the return type of the member functions begin and end is std::vector<int>::iterator.
        std::cout<< "\nITERATORS:\n";
        std::vector<int> v {1, 2};
        std::vector<int>::iterator beg_v = v.begin();
        std::vector<int>::iterator end_v = v.end();
        
        // There's an operator bool operator!=(std::vector<int>::iterator, std::vector<int>::iterator)
        std::cout << std::boolalpha;
        std::cout << (beg_v != beg_v) << std::endl;
        std::cout << (beg_v != end_v) << std::endl;

        // There are also operators
        // int& std::vector<int>::iterator::operator*() and
        // std::vector<int>::iterator& std::vector<int>::iterator::operator++()
        std::vector<int>::iterator it = beg_v;
        *it = 8; ++it;
        *it = 9; ++it;
        // Now if we reset it to the beginning we can see the contents of the first two locations is now 8 and 9!
        it = beg_v;
        std::cout << *it << std::endl; ++it;
        std::cout << *it << std::endl; ++it;

        // By this point we have seen that
        // v.begin() is like a pointer to the start of the vector and
        // v.end() is like a pointer just beyond the last element of the vector
        std::cout << (it != end_v) << std::endl;
        
        // For this reason we will introduce dummy nodes at the start and beginning of the linked list. This allows for the insert function
        
    }
    
    {
        std::cout << "\nOUR OWN LINKED LIST:\n";
        // Initialize linked list with nodes from 1-6.
        LinkedList ll {1,2,3,4,5,6};
        // Use range based for loop to iterate through the various elements.
        //Works because we have the *, ++, and != operator
        for (int val: ll){
            std::cout<< val << ' ';
        }
        std::cout<<"\n";
        Iterator end = ll.end();
        for (auto it = ll.begin(); it != end; ++it) {
            if (*it > 4){
                ll.insert(it, -8);
                break;
            }
        }
        
        for (int val: ll){
            std::cout<< val << ' ';
        }
        std::cout<<"\n";
        
        for (auto it = ll.begin(); it != end; ++it) {
            if (*it == 2){
                ll.erase(it);
                break;
            }
        }

        for (int val: ll){
            std::cout<< val << ' ';
        }
        std::cout<<"\n";
    }
    
    return 0;
}
