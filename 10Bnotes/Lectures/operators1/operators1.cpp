//
//  operators1.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 1/17/24.
//

#include <iostream>
#include "frac.hpp"

int main(){
    // Create some examples of fractions
    Frac w(-10,-30);
    Frac x;
    Frac y(2);
    Frac z(1,3);
    
    w.printFrac();
    x.printFrac();
    y.printFrac();
    z.printFrac();
    
    // Note that the member variables of our class are private, therefore we will need to be careful in how we access its values.
    
    // Compound assignment operators *=
    w*=z;
    (w).printFrac();
    
    // Add fractions and integers: note that as the member variables are private we can't access them outside the class. So lets overload these operators as member functions... as we will see this is not optimal!
    (w+2).printFrac();
    (w+z).printFrac();
    // This is all fine and good, but what about if we wanted to check 2+w? We can't write this overload as a member function as implicitly the left operand is a Fraction!
//    (2+w).printFrac();
    
    
    // Let us now implement multiplication outside the class in such a way that this isn't an issue! in doing so we will introduce the idea of using a friend function.
    (z*z).printFrac();
    
    // Hang on! Why does the following work? We haven't defined or implemented an operator overload for integer and fraction multiplication... The reason this work is that C++ performs implict conversions of types. The compiler knows how to multiply two integers and you've told it how to multiply two Frac types. However, while there is a rule to convert an integer to a Frac (see the constructors!) there isn't a rule for converting a Frac to an integer. Therefore the integer is converted to a Frac and then Frac multiplication is performed. This is nice as we don't need to overload the * operator multiple times, i.e., Frac*Frac, Frac*int and int*Frac1.
    (2*z).printFrac();
    (z*2).printFrac();
    
    // Lets finish up by likewise implementing equality comparison.
    std::cout << std::boolalpha << "z is equal to z? " << (z == z) << "\n";
    std::cout << "x is equal to y? " << (x == y) << "\n";
    // Check fraction to integer comparison
    std::cout << "y is equal to 2? " << (y == 2) << "\n";
    // Check integer to fraction comparison
    std::cout << "2 is equal to y? " << (2 == y) << "\n";
    
    return 0;
}




