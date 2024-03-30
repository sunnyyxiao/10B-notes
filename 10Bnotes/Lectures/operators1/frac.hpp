//
//  frac.hpp
//  PIC10B
//
//  Created by Sunny Xiao on 1/17/24.
//

#ifndef frac_hpp
#define frac_hpp

// ----------------------------------------------------------
// Frac clas
class Frac{
public:
    // Constructors
    Frac(const Frac& x); // copy constructor
    Frac(int _num, int _den);
    Frac(int _num);
    Frac();
    
    // Member functions
    void printFrac() const;
    bool checkIntEquality(const int& i) const;
    Frac under(const int& i) const;
    
    // Overloaded operators
    // General template: [type_returned] operator [operator_symbol] ([comma delimited list of operands])
    // Compound multiplication
    void operator *= (const Frac& right);
    // Addition
    Frac operator + (const Frac& right);
    // Friend functions: note although we declare these inside of Frac they are not member functions! They will in fact act as global functions but will have access to the private members of Frac
    // Multiplication
    friend Frac operator * (const Frac& left, const Frac& right);
    // Equality Comparison
    friend bool operator == (const Frac& left, const Frac& right);

private:
    int num;
    int den;
    void clean();
    void simplify();
};



#endif /* frac_hpp */


