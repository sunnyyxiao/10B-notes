//
//  frac.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 1/17/24.
//

#include "frac.hpp"
#include <cassert>
#include <iostream>
#include <cmath>


// ----------------------------------------------------------
// Frac class member function definitions
// Constructors
Frac::Frac(const Frac &x){
    num = x.num;
    den = x.den;
}
Frac::Frac(int _num, int _den):num(_num), den(_den){
    assert(den != 0);
    clean();
    simplify();
}
Frac::Frac(int _num):num(_num), den(1){}
Frac::Frac():num(0),den(1){}

// Member functions
void Frac::printFrac() const{
    std::cout << num;
    if(den!=1){std::cout << "/" << den;}
    std::cout << "\n";
}
void Frac::clean(){
    if (den<0){den *=-1; num *=-1;}
    if (num==0){den = 1;}
}
void Frac::simplify(){
    int a = abs(num);
    int b = den;
    //gcd(a,b) = gcd(b, a%b),gcd(a,0) = a
    while (b!=0){
        int temp = a%b;
        a = b;
        b = temp;
    }
    num /= a;
    den /= a;
}


// Overloaded operators
// Compound multiplication
void Frac::operator *= (const Frac& right){
    num = num*right.num;
    den = den*right.den;
    clean();
    simplify();
}

// Addition: note we are writing these as member functions to illustrate a point, it is actually better to implement these outside the class so that symmetry in operands can be achieved without overloading over and over again!
// Operator for Frac+Frac
Frac Frac::operator + (const Frac& right){
    Frac copy(right);
    copy.num = num*right.den + right.num*den;
    copy.den *= den;
    copy.clean();
    copy.simplify();
    return copy;
}

/*
 For multiplication we would encounter the symmetry issue if we implemented the * operator overload as a member function. Instead lets implement as a function outside the class, but declare it a friend of the class! This allows this function to access member variables. This is not always a good idea we might add, in particular it breaks the principle of encapsulation. But in this case we are not making any changes to the underlying objects so is not a problem really. Note we can also cleverly reuse our existing methods for compound multiplication to implement this function! Note we will also be able to use this function to multiply by a integer!
 Note that we do not need to add friend after adding friend in the hpp file
 */

//Note this is not void, it does not mutate the existing Frac object but creates a new one!
Frac operator * (const Frac& left, const Frac& right){
    Frac copy(left); // Here we are copying the Frac object 'left'. We'll dig into this in more detail when we get to memory management.
    copy.num*= right.num;
    copy.den*= right.den;
    return copy;
}
// Equality comparison
bool operator == (const Frac& left, const Frac& right){
    if ((left.den == right.den) && (right.num == left.num)){
        return true;
    }
    return false;
}
