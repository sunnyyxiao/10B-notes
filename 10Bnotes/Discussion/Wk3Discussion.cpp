//
//  Wk3Discussion.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 1/23/24.
//

#include <iostream>
#include <cmath>
#include <string>

/*
 Practice
 Create a class fraction that represents a fraction having a numerator and denominator.
 
 Use operator overloading for + and * to return fraction numbers which are the sum and product of two fraction numbers of the same class.
 
 Include a function to display the output of the fraction.
 Input two fraction numbers through main to check your result.
 
 Note: No need to simplify the fraction.
 */

class Fraction {
private:
    int num;
    int den;
    
public:
    Fraction(int _num, int _den): num(_num), den(_den){}
    Fraction(): num(0), den(1) {}
    
    Fraction operator + (Fraction& right){
        int newNum = num*right.den + den*right.num;
        int newDen = den*right.den;
        Fraction result(newNum,newDen);
        return result;
    }
    
    Fraction operator * (Fraction& right){
        Fraction result(num*right.num,den*right.den);
        return result;
    }
    
    void print(){
        std::cout << num << "/" << den << std::endl;
    }

};

int main(){
    
    std::cout << "What is your first fraction?";
    
    int num1, num2, den1, den2;
    
    std::cin >> num1;
    std::cin.ignore();
    std::cin >> den1;
    
    std::cout << "What is your second fraction?";
    
    std::cin >> num2;
    std::cin.ignore();
    std::cin >> den2;
    
    Fraction a(num1,den1);
    Fraction b(num2,den2);
    
    std::cout << "Multiplying these two fractions gives you ";
    (a*b).print();
    std::cout << "Adding these two fractions gives you ";
    (a+b).print();
    
    
    return 0;
}
