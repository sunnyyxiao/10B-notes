//
//  operators3.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 1/22/24.
//

#include <iostream>

struct A{
    explicit A(int _a): a(_a){} //maps integer to A object
    A (bool _a): a(10) {}
    
    void operator += (const A& right){
        a += right.a;
    }
    
    operator bool() const {//returns true if a is positive
        if (a>0) {
            return true;
        }
        return false;
    }
    
    int a;
};

struct B{
    B (int _b): b(_b){}
    int b;
};

//does not need to be a friend because structs are public
B operator * (const B& left, const B& right){
    return B(left.b*right.b);
}
//this function call is not allowed
B operator * (double d, const B& right) = delete;
B operator * (const B& left, double right) = delete;

class C{
public:
    C (int _i): i(_i),counter(0){}
    
    //can be const because counter is a mutable int
    int get() const { ++counter; return i;}
    //cannot make set const because you're mutating i
    void set(int _i) { ++counter; i = _i;}
    
    int member_function_calls_so_far_excluding_this_one() const{
        return counter;
    }
private:
    int i;
    //Use mutable in case you try to make a const instance of the class, then you can't read i or update the counter (update the counter every time it's being read)
    mutable int counter;
    //Some other irrelevant member variables used to demonstrate which types can be mutable
    mutable const int* p; //OK as pointer itself is not const
};

int main(){
    //Exploring explicit
    {
        std::cout << "Part A: explicit" << std::endl;
        
        A A1(5);
        A A2(true);
        A A3(-2);
        
        //Depending on which constructor we make explicit, implicit conversion will try to either convert true directly to an A type, or convert true to an int then to an A type! Depending on which constructor we make explicit we will see different outcomes!
        
        A1 += true;
        std::cout << A1.a << "\n";
        
        //Following is considered contextually explicit conversion! here we use the bool conversion to return a bool
        if (A1) {
            std::cout << "a is positive." << "\n";
        }
        
        //We have no * operation for struct A objects so is converted to a bool, then to an int!
        std::cout << A2*5 << "\n";
    }
    
    //Exploring delete:
    {
        std::cout << std::endl << "Part B: delete" << std::endl;
        
        B B1(2);
        B B2(4);
        std::cout << (B1*B2).b << "\n";
        //not allowed
//        std::cout << (2.0*B2).b << "\n";
//        std::cout << (B1*4.0).b << "\n";
//        std::cout << (B1*4).b << "\n"; //implicitly converts 4 to a double instead of using the constructor
    }
    
    //Exploring mutable:
    {
        std::cout << std::endl << "Part C: mutable" << std::endl;
        C C1(8);
        std::cout << C1.get() << std::endl;
        C1.set(88);
        std::cout << C1.get() << std::endl;
        C1.set(888);
        std::cout << C1.member_function_calls_so_far_excluding_this_one() << "\n";
        
        const C C2(8);
        std::cout << C2.get() << std::endl;
//        C2.set(88);
        std::cout << C2.get() << std::endl;
//        C2.set(888);
        std::cout << C2.member_function_calls_so_far_excluding_this_one() << "\n";
    }
    return 0;
}

