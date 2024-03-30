//
//  destructors_raii.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 2/9/24.
//

#include <iostream>

/*
 RAII (Resource Acquisition is Initialization)
 Programming technique that binds a resource such as heap memory to the lifetime of an object. When the corresponding object is properly implemented, it will acquire the relevant resources that it needs during its construction and will automatically release them at the end of its life cycle. We will use a destructor to automatically manage the deallocation of heap memory when an object goes out of scope.
 Destructors
 - declared like a constructor but with a ~ in front
 - neither requires any argument nor returns any value
 - cannot be overloaded, and is the only way a class object can be destroyed
 */

struct A{
    A(int _i):i(_i){}
    A():i(0){}
    
    ~A(){std::cout << "Destructor of A object with i value " << i << " called." << std::endl;}
    
    int i;
};

struct RAII{
    RAII(int _i, int _j, double _d, size_t _l, int _a): i(_i), pi(new int(_j)), pad(new double [_l]{_d}), l(_l), pA(new A(_a)){}
    RAII():i(0), pi(new int(0)), pad(new double [5]{1}), l(0), pA(new A(0)) {}
    
    ~RAII(){
        std::cout << "Destructor for RAII object called.\n";
        delete pi;
        delete[] pad;
        delete pA;
        std::cout << "Destructor for RAII object completed.\n";
    }
    
    friend std::ostream& operator << (std::ostream& os, const RAII& r){
        os << "Contents of RAII object: " << std::endl;
        os << "i value = " << r.i << ", i memory = " << &r.i << std::endl;
        os << "pi value = " << r.pi << ", pi memory = " << &r.pi << ", *pi value is " << *r.pi << std::endl;
        os << "pad value = " << r.pad << ", pad memory = " << &r.pad << std::endl;
        for (size_t i = 0; i < r.l; i++){
            os << r.pad+i << " " << *(r.pad+i) << " ";
        }
        os << "pA value = " << r.pA << ", pA memory = " << &r.pA << ", pA->i value is " << r.pA->i << std::endl;
        
        return os;
    }
    
    int i;
    int* pi;
    double* pad;
    size_t l;
    A* pA;
};

int main(){
//    {
//        A a1(2);
//        //Can call directly but not supposed to do this
////        a1.~A();
//        std::cout << "Leaving local scope." << std::endl;
//    }
//    //Destructor function called as we go out of scope
//    std::cout << "Back in main." << std::endl;
    
    {
//        RAII b1;
//        std::cout << b1;
        
        //Single explicitly constructed RAII object
        RAII b2(1,2,7.5,3,8);
        
        //Single explicitly constructed RAII object stored on the heap
        RAII* p1 = new RAII(3,4,3.9,6,9);
        
        std::cout << "b2 MEMBERS: \n" << b2 << "\n\np1 MEMBERS:\n" << *p1;
        
        delete p1;
        std::cout << "Leaving local scope." << std::endl;
    }
    std::cout << "Back in main." << std::endl;
    //Without initializing a destructor, default destructor simply leaves the objects on the heap, leading to concern for a memory leak
    
    return 0;
}
