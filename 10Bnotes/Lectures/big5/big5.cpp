//
//  big5.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 2/28/24.
//

/*
 Big 5
 - destructor
 - copy constructor
 - move constructor
 - copy assignment
 - move assignment
 
 1. If you need to write one of the big five, it's probably a good idea to write all of them!
 2. If you need to explicitly put an object on the heap, it's also a good idea to write all of them!
 */

#include <iostream>
#include <utility>
#include <vector>
#include "string.hpp"


namespace detail {
    template <class T> struct value_category      { static constexpr char const* value = "prvalue"; };
    template <class T> struct value_category<T&>  { static constexpr char const* value = "lvalue"; };
    template <class T> struct value_category<T&&> { static constexpr char const* value = "xvalue"; };
}
#define PRINT_VALUE_CAT(expr) std::cout << #expr << " is a " << ::detail::value_category<decltype((expr))>::value << '\n';


// Use this struct to identify where temporary objects are stored!
struct X {
    // Use default constructor, destructor etc..
    // Following function returns a pointer to the instance of X in question
    X* get_address()       { return this; }
};

// We'll use the same struct from last time to explore why move is good!
struct B{
    B(int _i, double _d):i(_i), p(std::make_shared<double>(_d)){std::cout<<"Parameterized constructor called!\n";}
    B():i(0), p(std::make_shared<double>(0)){std::cout<<"Default constructor called!\n";}
    B(const B& a):i(a.i), p(std::make_shared<double>(*(a.p))){std::cout<<"Copy constructor called!\n";}
    B(B&& b){
        std::cout<<"Move constructor called!\n";
        i = b.i;
        std::swap(p, b.p);
    }
    ~B(){std::cout<<"Destructor called!\n";}
    B& operator=(B&& right){
        std::cout<<"Move assignment operator called!\n";
        i = right.i;
        std::swap(p, right.p);
        return *this;
    }
    B& operator=(const B& right){
        std::cout<<"Copy assignment operator called!\n";
        i = right.i;
        p = std::make_shared<double>(*(right.p));
        return *this;
    }

    friend B operator + (const B& left, const B& right){
        double l = 0;
        double r = 0;
        if (left.p != nullptr){l = *left.p;}
        if (right.p != nullptr){r = *right.p;}
        B temp(left.i + right.i, l+r);
        return temp;
    }
    
    // Write swap based on copy...
    friend void my_swap_copyB(B& b1, B& b2){
    // Here the copy assignment constructor and operator are called as b1, b2 and b3 are lvalue expressions!
        B b3(b1);
        b1 = b2;
        b2 = b3;
    }
    
    // Write swap based on copy...
    friend void my_swap_moveB(B& b1, B& b2){
    // Here the copy assignment constructor and operator are called as std::move(b1), std::move(b2) and std::move(b3) are rvalue (specifically xvalue expressions!
        B b3(std::move(b1));
        b1 = std::move(b2);
        b2 = std::move(b3);
//        b1 = std::move(b2);
    }
    
    // integer data member variable on the stack
    int i;
    // pointer data member, points to a double on the heap
    std::shared_ptr<double> p;
};


/*
 We'll use these later to show that returning a const value is bad.
*/
basic::string f() {
    return basic::string("for moving");
}
const basic::string g() {
    return basic::string("for moving");
}




int main() {
    
    // Notes on std::move
    {
        std::cout << "Getting the address of temporary objects:\n";
        X x;
        // std::move converts an l-value to an x-value.
        PRINT_VALUE_CAT(x)
        PRINT_VALUE_CAT(std::move(x))
        
        // We cannot take the address of an x-value directly.
        // Therefore, the following line gives an error...
        // std::cout << &std::move(x) << std::endl;

        // Although we cannot ask for the memory address of
        // a temporary directly, the following print statement confirms
        // that it does have a place in memory, in fact on the stack!
        std::cout << X().get_address() << std::endl;
        // Temporary objects are nearly always stored on the stack for efficiency purposes!
        
        // Finally then we can observe that move dosn't actually move anything!!! Just casts an lvalue to an xvalue.
        std::cout << &x << std::endl;
        
        //We are not allowed to ask for its memory address as it is now an x value, but it still does have a place on the stack
        std::cout << std::move(x).get_address() << std::endl;
        
        std::cout << "\nSwap example:\n";
        // motivating std::move using swap!
        B b1(1,1.1);
        B b2(2,2.2);
        std::cout << "double value of b1 and b2 is " << *b1.p << " and " << *b2.p << "\n";
        // See what happens if you use the copy or move versions of swap...
        my_swap_moveB(b1,b2);
        
        //standard library also uses move semantics, so std::swap(b1,b2) would be fine too
        std::cout << "double value of b1 and b2 is " << *b1.p << " and " << *b2.p << "\n";
        
        // In short, swapping is an example where using copy would be very inefficient. However, to use our move assignment operator we need the argument to be an rvalue whereas all of our variables are clearly lvalues! By using std::move we can cast them in a sense to being xvalues thereby allowing us to call the mover operator.
    }
    
    
    std::cout<< "\n!!!! String example !!!! :\n";
    {
        /*
         STRING EXAMPLE
         Now we've seen an abstract example
         showing how the function calls are resolved,
         we can see a more useful example
         where our move constructor and move assignment operator
         lead to more a more efficient class.
        */
        basic::string s1("str1");
        basic::string s2("STRING2");
        const basic::string c("const");


        basic::string copy(s1);
        std::cout << copy << ' ' << s1.size() << std::endl;
        basic::string move(std::move(s1));
        std::cout << copy << ' ' << move << ' ' << s1.size() << std::endl << std::endl;
        // The moved-from object s1 is now storing the empty string due to the std::move
        // Although it has been stolen from, it is in a valid state!


        copy = s2;
        move = std::move(s2);
        std::cout << copy << ' ' << move << ' ' << s2 << std::endl << std::endl;
        // The moved-from object s2 is storing move's old data, which is s1's original data. Basically a swap, so that move and s2's data swap with one another.
        // Although it has been stolen from, it is in a valid state!

        // Note: it seems common for compilers to implement
        // std::string::operator=(std::string&&)
        // in such a way that the moved-from object is the empty string;
        // we have not done this for our basic::string::operator=(basic::string&&).


        move = std::move(c);
        std::cout << move << ' ' << c << std::endl << std::endl;
        // A const object cannot be moved-from since that would violate 'const', this calls the copy assignment operator because we cannot use move semantics.

        s1 = "test"; std::cout << s1 << std::endl << std::endl;
        s1 = 't';    std::cout << s1 << std::endl << std::endl;
        // basic::string::operator=(const char*) and basic::string::operator=(char)
        // implicitly make use of basic::string::operator=(basic::string&&).
        // the literals are treated as temp string objects, destructor then called on the temp object


        move = f();
        std::cout << move << std::endl << std::endl;
        // f() is a pr-value and so basic::string::operator=(basic::string&&) is used.

        move = g();
        std::cout << move << std::endl << std::endl;
        // g() returns a const value and so
        // basic::string::operator=(basic::string&&) cannot be used.
        // DO NOT RETRUN A CONST VALUE! Doing so prevents move semantics.


        std::cout << std::endl;
        
    }
    
    return 0;
}



