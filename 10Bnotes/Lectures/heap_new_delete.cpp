//
//  heap_new_delete.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 2/5/24.
//

#include <iostream>
#include <vector>

/*
 Stack
 - 'static' memory allocation is determined in advance
 - memory allocation handled by compiler
 - stack is LIFO
 - fast but less flexible
 
 Heap
 - "dynamic" memory allocation during runtime
 - memory allocation handled by us
 - free and unrestricted but slow
 */

int eight(){return 8;}

struct A{
    A (int _i):i(_i){};
    int i;
};

struct B{
    B(int _i):i(_i){};
    B():i(10){};
//    void blah() const{std::cout << "this is a void member function of B" << std::endl;}
    int i;
};

struct C{
    C(int _i, int _j):i(_i),j(_j){};
    C():i(0),j(0){};
    int i;
    int j;
private:
    int k;
};

int main(){
    /*
     Memory leak is when something is sitting on the heap, and the pointer that can access it goes out of scope
     New operator allocates memory for and creates an object on the heap and then returns the memory address of said obejct on the heap; this is important in order to read and write to a heap object we need to have a pointer on the stack pointing at it
     New[] operator allocates memory for an array of objects! This operator allocates a contiguous block of memory to store a sequence of objects, the number of which is given as an arguemnt, e.g. 'new int[8]' creates an array of integers on the heap. However, unlike a static array, the array size parameter doesn't need to be const
            - default-initialized (for fundamental types this means uninitialized)
            - value-initialized (fundamental types would be set to 0)
            - if the first several values are set by the user, the remaining values will be value initialized
     
     Delete operator deallocates memory in the heap, in effect destroying the object at said address and freeing up the memory location to be used by some other object. One should always delete an object before all pointers at said object go out of scope.
     Delete[] operator deallocates a contiguous array on the heap.
     
     */
    
    //Demonstrating stack vs heap memory for arrays vs vectors
    {
        std::cout << "Where are arrays and vectors stored?" << std::endl;
        std::cout << "Printing out contents of array: " << std::endl;
        int a1[] = {2,3,4};
        int* pi = a1;
        for (size_t i = 0; i < 3; i++){
            std::cout << (pi+i) << " " << *(pi+i) << "\n";
        }
        
        std::cout << "Printing out contents of vector: " << std::endl;
        std::vector<int> v1 = {5,6,7};
        pi = &v1[0];
        for (size_t i = 0; i < 3; i ++){
            std::cout << (pi+i) << " " << *(pi+i) << "\n";
        }
    }
    
    int *pim1;
    int *pim2;
    
    {
        
        std::cout << "\nExplicit, value and default initialized objects on the heap" << std::endl;
        int* pi1 = new int(8); // explicitly initialized, integer object has value 8
        int* pi2 = new int(); //value-initialized, integer object has value 0
        int* pi3 = new int; //default-initialied, integer object left uninitialized
        
        //pi1, pi2, and pi3 are stack variables, but once the scope ends, they wil be popped off --> three objects are simply sitting on the heap
        
        delete pi2;
        delete pi3;
        //best practice to assign to nullptr as per notes
        pi2 = nullptr;
        pi3 = nullptr;
        
        //pointing an int main pointer at the heap integer with value 8
        pim1 = pi1;
        //Pim1's memory address = stack object, value stored by pim1 is a heap memory address
        std::cout << &pim1 << " " << pim1 << " " << *pim1 << "\n";
        
        //Now let's point a global pointer at a stack integer with value 9 just for contrast
        int x = 9;
        pim2 = &x;
        //Both memory addresses are stored on the stack
        std::cout << &pim2 << " " << pim2 << " " << *pim2 << "\n";
    }
    
//    std::cout << *pi1 << "\n"; //this will of course give an error, pi1 was a local pointer which has now ceased to exist as resided on the stack
    
    std::cout << *pim1 << "\n"; //this works fine, recall heap objects are global
    //using a pointer to bind to something local on the stack is dangerous; this can be overwritten at any time, so it cannot be trusted
//    std::cout << *pim2 << "\n";
    
    delete pim1;
    pim1 = pim2 = nullptr;
    
    {
        std::cout << "\nPutting arrays on the heap:\n";
        int* pai1 = new int[8]{1,2,3}; //construction parameter passed for first 3 ints
        int* pai2 = new int[8]{}; //value-initialized
        int* pai3 = new int[8]; //default-initialized
        int* pai4 = new int[eight()]; // okay to use a size that is not known at compile time
        
        delete[] pai1;
        delete[] pai2;
        delete[] pai3;
        delete[] pai4;
        
        //Strictly not ncecessary as once we exit this scope these pointers will be destroyed! But if they were global would be good practice to set to the nullptr as illustrated below
        pai1 = pai2 = pai3 = pai4 = nullptr;
    }
    
    {
        std::string* pas1 = new std::string[8]{"A","B","C"};
        std::string* pas2 = new std::string[8]{};
        std::string* pas3 = new std::string[8];
        
        delete[] pas1;
        delete[] pas2;
        delete[] pas3;
        pas1 = pas2 = pas3 = nullptr;
    }
    
    //Creating and destroying user defined objects
    {
        std::cout << "\nCreating and destroying user defined objects:\n";
        B *pB1 = new B; //works fine as B has default constructor
        
//        A *pA = new A; //does not work, no default constructor
        
        delete pB1; //creates a destructor that deletes everything associated with the object
        pB1 = nullptr; // B1 will be in scope for a bit so good idea to set to nullptr
        
        //can also create an array of type A or B objects and store them on the heap
        B *pB2 = new B[2](); //value-initialized so default constructor is used
        std::cout << (pB2+1)->i << "\n";
        
        B *pB3 = new B[2]; //default-initialized
        std::cout << (pB3+1)->i << "\n";
        
        B *pB4 = new B[2] {2,3}; //passes argument to constructor
        std::cout << (pB4)->i << "\n";
        
        C *pC1 = new C[2] {C(1,2), C(3,4)};
        std::cout << pC1->i << " " << pC1->j << "\n";
        std::cout << (pC1+1)->i << " " << (pC1+1)->j << "\n";
        
        delete[] pB2;
        delete[] pB3;
        delete[] pB4;
        delete[] pC1;
    }
    
    //There is a better way of doing this through smart pointers
    
    return 0;
}

