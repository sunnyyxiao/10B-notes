//
//  testing.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 3/19/24.
//

#include <iostream>

class A{
public:
    A():a(0){}
    A(int _a):a(_a){std::cout << "parameterized constructor\n";}
    A(const A& r):a(r.a){
        std::cout << "copy constructor of a called\n";
    }
    int a;
};

class B : public A{
public:
    using A::A;
    
    int b;
};

int main(){
//    A a(1);
//
//    B b(2);
//    std::cout << b.b << "\n";
//    B b2(b);
//    std::cout << b2.a << " " << b2.b << "\n";
//
//    int x = 2;
//
//    int* p = &x;
//    {
//        std::shared_ptr<int> c = std::make_shared<int>(9);
//        std::weak_ptr<int> c2 = c;
//        std::cout << c.use_count() << "\n";
//        p = c.get();
//    }
//    std::cout << (p == nullptr) << "\n";
//
//
//
//    std::shared_ptr<int> c3 = std::make_shared<int>(10);
    
//    {
//        int* p = new int[9];
//        for (size_t i = 0; i <9; i++){
//            *(p+i) = i;
//        }
//        for (size_t i = 0; i <9; i++){
//            std::cout << *(p+i) << " ";
//        }
//    }
    
    A a1(A(1));
    
    return 0;
}
