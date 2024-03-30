//
//  fundamentals2.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 1/10/24.
//

#include <iostream>
#include <string>
#include "functions.hpp"

using namespace std;

// FUNCTIONS
/* One of the key programming principles is modularity. This allows us to build complicated programs as an assembly of sub-programs, also called routines or functions! Recall int main() is a function which acts as the entry point of our program (i.e., your computer will execute the instructions in the source code you have written starting with the first instruction in int main() and will proceed from there). Instead of writing all the instructions in int main(), we can call other functions from inside int main() thereby outsourcing certain tasks.
 
 
 Writing a function consists of the following steps
  - writing a function signature,
  - writing a docstring describing purpose of function, inputs and output variables,
  - writing the body of the function, i.e., the sequence of instuctions.
  - returning a value (maybe)

 Function template:
 
  type_returned function_name(type1 arg1, type2 arg2...)
  {
     Docstring
     Function body or definition
  }
 
 Observe function definitions introduce a block scope! Local variables defined inside a function are therefore not accessible inside main. Note that functions cannot be declared and defined locally in C++, i.e., within a {} pair of brackets.
 ** Usually functions are declared/defined in a separate cpp/hpp pair of files, since then the compiler doesn't need to constantly run through all of the function definitions (which can be expensive if the functions are long and complicated). Including the hpp allows us to link the functions/main program at the linker stage. Including a cpp file would combine the two at the preprocessing stage since the preprocessor copies the cpp contents to the top of the main function.
 */

//Example my_abs to return absolute value of an int: declare and define
int my_abs(int x){
    if (x < 0){
        return -x;
    }
    return x;
}

// Example my_max: here we declare first and define at the bottom. Note we only need to declare a function before we reference it in our code, it will still build if we declare, reference then define. Note we often keep the docstring and declaration together.
int my_max(int x,int y);

// Typically we do not declare or define our functions inside of main.cpp, if we do this it is hard for us to reuse them in other programs and also is inefficient from a compilation perspective as we will shortly discuss. Instead we put function declarations in a header file and function definitions in a seperate cpp file.

//References example my_swap: take two integers and swap them! Implement as procedure
void my_swap(int& x, int& y){
    int temp = x;
    x = y;
    y = temp;
}

int main(){
    
    {
        // Function examples:
        
        //Absolute value
        cout << my_abs(-4) << endl;
        
        //Max value
        cout << my_max(3,9) << endl;
        
    }
    {
        //Cpp + hpp functions
        
        //Prob_bday
        cout << prob_bday(60) << endl;
    }
    {
        //  REFERENCES AND THE & OPERATOR
        //  Variables copy data from one location in memory to another. Although they often look like variables syntax wise, references are not variables! Instead, they are 'new' names or aliases for an existing variable (location in memory). To declare a reference you just add an & after the type, which indicates the object in question a an alias for a variable of said type.
        {
            //Basic examples on references
            int x = 2;
            int& r = x; //references must be initialized when declared
            cout << r << endl;
            r = 3;
            cout << x << endl;
            int y = 3;
            r = y;
            
            cout << boolalpha << (r == x) << endl;
            const int& z = 4;
        }
        /*
         Notes on references:
         - When you declare a reference, it must at the same time also be initialized or bound to another variable that has already been declared. This is done via the assignment operator.
         - Note that references like any object name have a scope!
         - Once a reference has been bound to a variable it will always reference that variable, it cannot be bound to a new variable!
         - As a result, the boolean r==i is always true for the rest of the runtime of the program in which the underlying variable is in scope. Therefore, whenever we reference the name i or r they will both have the same value (so long as they are in scope)!
         
         So what are references used for? Their primary use is in function arguments! Instead of passing by assignment one can instead pass by reference, which creates a local alias inside a function for a global variable. This allows us to mutate global variables inside of a function without returning and assigning.
         */
        {
            //Swap function implementation
            int x = 1;
            int y = 2;
            my_swap(x,y);
            cout << x << " " << y << endl;
        }
        // Passing arguments by reference is more efficient than by assignment as one dosn't need to copy a potentially large amount of data to a new location. However what if you don't want to risk changing the variable? Constant references are like normal references but you aren't allowed to assign via them!
        {
            //const references versus non-const references examples
            int x = 2;
            int& r1 = x;
            const int y = 3;
            //int& r2 = y;
            const int& r2 = y;
        }
        /* When should we pass by reference vs. const. reference vs assigment? Two things to consider,
         1) Do we actually want to perform a mutation on the argument, i.e., do we want to change the value of the argument by calling a function?
         2) Is the argument variable large in terms of memory? In particular fundamental types we covered at the start are perhaps at most 64 bits or 8 bytes. This is not expensive to copy. On the other hand containers, like vectors or maybe even strings, could in theory take up a lot of memory and therefore be expensive to copy.
         */
        {
            // The & operator: when the & is used on the left hand side of an assignment it is for declaring a reference, when it is on the right hand side it is used to access the memory address of the variable in question.
            
            //Memory access with &
            int x = 2;
            cout << &x << endl;
        }
    }
    {
        // POINTERS:
        /*
         Pointers are variables used for storing the memory addresses of other variables: the value of a pointer is a memory address! To declare a pointer you add a * after the type.
         */
        {
            int x = 2;
            int y = 3;
            int* p = &y;
            cout << *p << " " << p << endl;
            *p = 10;
            cout << y << endl;
            p = &x;
            cout << *p << " " << p << endl;
            
            int* p1 = &x;
            //pointer to constant integer
            const int* p2 = &x;
            //pointer that is constant
            int* const p3 = &x;
            const int* const p4 = &x;
            
            //Can reassign p1 and p2, but not p3 or p4
            //Can modify the value of p1 and p3, but not p2 or p4
            
            //*p2 = 4;
            *p3 = 4;
            
            p2 = &y;
            //p3 = &y;
        }
        {
            // It is not a good idea to declare and not initialize a pointer... Why? Well if our pointer happens to point to some random location which is storing something important we may inadvertantly overwrite some important piece of information...
            int y = 12;
            int* p2 = nullptr; // special memory address which makes sure that if you derefence then will throw an error. If you can't initialize a pointer immediately initialize as the nullptr.
        }
    }
    return 0;
}

//My_max definition at bottom
int my_max(int x,int y){
    if (x>y){
        return x;
    }
    return y;
}

