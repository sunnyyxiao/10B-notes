//
//  mt1.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 2/12/24.
//

#include <iostream>
#include <vector>

using namespace std;

class B{
public:
    B(int _x):x(_x){}
    B():x(0){}
    virtual void foo() const = 0;
    virtual B& operator ++ () final{
        ++x; return *this;
    }
protected:
    mutable int x;
};

class C : public B{
public:
    C(int _x, int _y):B(_x),y(_y){}
    C():B(),y(0){}
    void foo() const override {
        cout << "C " << x << " " << y << endl;
    }
    
    int y;
};

class D : public C{
public:
    D(int _x, int _y, int _z):C(_x,_y),z(_z){}
    virtual void foo() const override{
        cout << "D " << x << " " << y << " " << z << endl;
    }
    int z;
};


int main(){
    {
        C c1(4,5);
        std::cout << c1.foo() << "\n";
    }
    
    {
        C c1(6,7);
        ++c1;
        std::cout << c1.foo() << "\n";
    }
    
    {
        C c1(8,9);
        ++(++c1);
        std::cout << c1.foo() << "\n";
    }
    
    {
        const C c1(10,11);
        ++c1;
        c1.foo();
    }
    
    
    return 0;
    
}
