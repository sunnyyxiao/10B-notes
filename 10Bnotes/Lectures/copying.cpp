//
//  copying.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 2/21/24.
//

#include <iostream>

/*
 Deep vs shallow copy
 Shallow copy: call the copy assignment operator (or assignment operator) on all data members of an object, assigning them to corresponding data members in another object of the same type. Data members corresponding to variables like ints and doubles are copied across entirely. For pointers, the two pointers just point at the same object, but the underlying data is not duplicated.
 Deep copy: data members of a class are copied, as well as underlying data. For example, deep copy would create a duplicate double on the heap instead of sharing one.
 
 Copy elision merges multiple copies into one copy. Formally, copy elision is an optimization implemented by most compilers.
 1. NRVO (Named Return Value Optimization): If a function returns a class type by value and the return statement's expression is the name of a non-volatile object (meaning the compiler decides where it is located, this is nearly always the case for us) with automatic storage duration (Which isn't a function parameter), then the copy/move that would be performed by a non-optimizing compiler can be omitted. If so, the returned value is constructed directly in the storage to which the function's return value would otherwise be moved or copied.
 2. RVO (Return Value Optimization): If the function returns a nameless temporary object that would be moved or copied into the destination by a naive compiler, the copy or move can be omitted as per 1
 */

//Write a struct with an integer on the stack double on the heap
struct A{
    A():i(0),p(nullptr){
        std::cout << "Default constructor called" << std::endl;
    }
    A(int _i, double _d):i(_i),p(new double(_d)){
        std::cout << "Parameterized constructor called with i = " << _i << ", double = " << _d << std::endl;
    }
    ~A(){
        if (p != nullptr){
            std::cout << "Destructor of A object with i = " << i << ", *p = " << *p << " called" << std::endl;
            delete p;
        }
        else std::cout << "Destructor of A object with i = " << i << ", *p = nullptr called" << std::endl;
    }
    A(const A& r):i(r.i),p(new double(*(r.p))){
        std::cout << "Deep copy constructor called, copying over i = " << i << ", *p = " << *p << "\n";
    }
//    Not good to combine shallow copy with non-smart pointers
//    A(const A& r):i(r.i),p(r.p){
//        std::cout << "Shallow copy constructor called, copying over i = " << i << ", *p = " << *p << "\n";
//    }
    
    //Copy assignment can be deep or shallow
    A& operator = (const A& r){
        std::cout << "Deep copy operator called, copying over i = " << r.i << ", *p = " << *(r.p) << "\n";
        i = r.i;
        delete p;
        p = new double (*(r.p));
        return *this;
    }
    double *p;
    int i;
};

A operator + (const A& l, const A& r){
    std::cout << "Addition operator for type A called\n";
    return A(l.i + r.i, *(l.p) + *(r.p));
}

//Pointless function to illustrate ellision
A f(){
    return A();
}

int main(){
    std::cout << "Shallow versus deep copy:\n";
    {
        A a1(1,2.2);
        A a2 = a1;
        std::cout << std::boolalpha << (a1.p == a2.p) << std::endl;
    }
    
    std::cout << "\nCopy construction versus assignment versus direct construction\n";
    {
        std::cout << "a1:\n";
        A a1(1,2.2);
        std::cout << "a2:\n";
//        A a2;
        A a2(a1);
//        A a2 = a1; //uses copy constructor, not operator
//        a2 = a1;
        
        std::cout << "a3:\n";
        //Compiler recognizes what is being built by the addition operator, only calls parameterized constructor once but not copy constructor, an example of copy elision
        A a3 = a1 + a2;
        
        std::cout << "f():\n";
        A a4 = f();
    }
    
    // Scenarios where copying is expensive
    std::cout << "\nCOPYING CAN BE EXPENSIVE:\n";
    {
        // Example 1:
        A a1(3,2.5);
        A a2 = a1;
        // ... some stuff happens...
        // ... now suppose we want to reset to the defualt for instance!
        std::cout<<"Performing a1 = A()\n";
        a1 = A();// Some compilers might show this also as a copy elision but mine dosn't. In short its not always easy to anticipate outside the two cases specified in the notes, and depends on your compiler!
        // Line above first creates an object A somewhere, but not somewhere we have access to, is not in 'our' memory, its an object our machine is handling. Then copies over the data to a1. Wouldn't it be better if we could just create the A object once?
        std::cout<<"Performing a3 = a1+a2\n";
        A a3 = a1 + a2;
        // What happened to the above!!! We see the parameterized constructor is called but surprisingly no call to the copy constructor or copy assignment operator! A copy elision has taken place, in particular an NRVO!
        
        std::cout<<"Calling f()\n";
        A a4 = f();
        // Again we see the default constructor is only called once. An RVO has taken place!
    }
    
    return 0;
}

/*
 Exercise
 - write a struct which models a vehicle (brand, color, max number of occupants)
 - one member variable must be an array on the heap with occupants of the vehicle
 - impelments a deep copy constructor
 - implement a shallow copy assignment operator
 */

struct Vehicle{
    Vehicle(std::string _brand, std::string _color, size_t _max, double _fuel_eff): brand(_brand), color(_color), max(_max), p(new std::string [_max]), fuel_eff(_fuel_eff){}
    Vehicle():brand(""),color(""),max(0),p(nullptr){}
    ~Vehicle(){
        std::cout << "Destructor for vehicle of brand " << brand << " called\n";
        delete [] p;
    }
    
    Vehicle(const Vehicle& r):brand(r.brand),color(r.color),max(r.max),p(new std::string [r.max]),fuel_eff(r.fuel_eff){}
    
    Vehicle& operator = (const Vehicle& r){
        delete[] p;
        brand = r.brand;
        color = r.color;
        max = r.max;
        fuel_eff = r.fuel_eff;
        p = r.p;
        return *this;
    }
    
    std::string brand;
    std::string color;
    size_t max;
    double fuel_eff;
    std::string* p;
};

