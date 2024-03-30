//
//  memory_types.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 2/2/24.
//

#include <iostream>

/*
 Four broad categories of abstract memory
 - code memory: machine level instructions for all functions (global and member) are stored; as a program runs instructions are read from code memory and executed
    - initialized at startup
    - executable
    - read only
 - (global) static memory: this is where all global variables and static variables are stored
    - startup unit
    - non-executable
    - read and write
 - stack memory: most C++ variables are stored here; all local non-static variables reside on the runtime stack
    - allocation and deallocation handled by compiler
    - non-executable
    - read and write
    - less flexible than the heap, but more efficient
    - need to know the memory size of the variable
    - grows down (memory address decreases as you keep going)
    - when function call ends, all the allocated memory variables are popped off the stack
 - heap memory: this category of memory is used for storing objects dynamically (allowing their requirements to change during runtime)
    - don't need to know size of objects
    - less efficient than the stack, but more flexible
    - managed by the programmer
    - good for std arrays and vectors
    - grows up (memory address increases as you continue)
 
 Low to high address (0x00...): code --> static --> heap --> stack
 */

int gcounter = 0; //initialized only once before main is run

void gcounted(){
    std::cout << "gcounted has been called " << ++gcounter << " times\n";
}

void scounted(){
    //Initialized only once before main is run
    static int scounter = 0;
    std::cout << "scounted has been called " << ++scounter << " times\n";
}

void lcounted(){
    int lcounter = 0;
    std::cout << "lcounted has been called " << ++lcounter << " times\n";
}

int do_stuff(int x){
    std::cout << &x << "\n";
    int z = 2;
    std::cout << &z << "\n";
    //upon returning this, x and z are deallocated
    return x*z;
}

int main(){
    std::cout << "Static example:\n";
    {
        gcounted();
        scounted();
        lcounted();
        
        
        gcounted();
        scounted();
        lcounted();
        
        gcounted();
        scounted();
        lcounted();
    }
    
    std::cout << "Stack example 1:\n";
    
    {
        int x = 1;
        std::cout << &x << "\n";
        int y = 2*x;
        std::cout << &y << "\n";
        {
            int y = 2*x;
            std::cout << &y << "\n";
        }
        //Note we don't start using the stack addresses corresponding the variables which have ceased to exist!
        int z = 2*y;
        std::cout << &z << "\n";
    }
    
    std::cout << "\nStack example 2:\n";
    {
        int x = 4;
        std::cout << &x << "\n";
        {
            int y = x;
            std::cout << &y << "\n";
            //Note local variables in function are stored not quite contiguously with those in main, but will be stored from higher address to lower address (top to bottom) still
            
            //memory address jumps down during a function call, function calls require more things such as a pointer to ensure we go back to where we were in int main()
            y = do_stuff(y);
            //value of y is overwritten to be 8, local function x and z variables are popped off the stack
        }
        //memory address returns back to where it last was in int main(), ex.) 184->180
        int w = 0;
        std::cout << &w << "\n";
    }
    
    return 0;
}
