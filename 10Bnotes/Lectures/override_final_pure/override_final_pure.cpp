//
//  override_final_pure.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 1/31/24.
//

#include "employees2.hpp"
#include <iostream>

/*
 Override and final example
 - ex1 is suposed to be overridden
 */

struct A{
    A():x(1){}
    double x;
    virtual double ex1 (int b){
        return b*x;
    }
    virtual void ex2(){
        std::cout << "ex2 of class A\n";
    }
};

struct B : public A{
    
//     Example 1: override
//     Here we meant to override ex1 but made a mistake in the parameter type!
//    virtual double ex1(double b){
//        return b*b*x;
//    }
    //This will not build, alerting us to the error in our declaration of the override!
//    virtual double ex1(double b) override{
//        return b*b*x;
//    }
    virtual double ex1(int b) override{
        return b*b*x;
    }
    
    //This one cannot be overridden if final keyword is used
    virtual void ex2() override /*final*/{
        std::cout << "ex2 of class B\n";
    }
};

struct C : public B{
    //This will throw an error if we declare ex2 as final in class B
    virtual void ex2() override{
        std::cout << "ex2 of class C\n";
    }
};

int main(){
    
    {
        A a;
        B b;
        std::cout << a.ex1(10) << "\n";
        std::cout << b.ex1(10) << "\n";
    }
    
    {
        B b;
        C c;
        b.ex2();
        c.ex2();
    }
    
    /*
     Example 3:
     We will reimplement the same worker contracter classes to model payroll. Howeve,r this time we will not build Contractor on top of Worker, instead we will create an abstract Employee class and build workers and contracters from Employee. This makes quite a lot of sense: employees with regards to Payroll are either workers or Contracters, so we would never want to create Employee objects. The Employee object instead allows us to
     */
    {
//        Employee e1; //can't instantiate instances of an abstract class
        Worker w1;
        Contracter c1;
        
        std::cout << "$" << w1.wage(45) << ", $" << c1.wage(45) << "\n";
    }
    
    return 0;
}
