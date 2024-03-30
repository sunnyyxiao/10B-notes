//
//  mttest.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 2/6/24.
//

#include <stdio.h>
#include <iostream>

class B{
public:
    explicit B(double _x):x(_x),i(0),j(0){}
    virtual void operator += (B& r){
        i++;
        x+= r.x;
    }
    virtual std::string info (float d) const{
        j++;
        return "Type B object";
    }
    
    double x;
    int i;
    
    
protected:
    mutable int j;
//    virtual std::string info (float d) const{
//        j++;
//        return "Type B object";
//    }
};

class C: public B{
public:
    using B::B;
    virtual std::string inf() const{
        j++;
        return "Type C object";
    }
};

struct Pet{
    Pet(std::string _species):species(_species){}
    virtual void noise() const = 0;
    std::string species;
};

struct Dog: public Pet{
public:
    Dog(bool _fluffy):Pet::Pet("dog"),fluffy(_fluffy){}
    virtual void noise() const override{
        std::cout << "Woof!\n";
    }
    bool fluffy;
    
};

struct Corgi: public Dog{
    using Dog::Dog;
    virtual void noise() const override{
        std::cout << "Royal woof!\n";
    }
    bool fluffy;
};

class A{
public:
    A(int _x):x(_x){}
    
//    A& operator () ++ {
//        x++;
//        return *this;
//    }
    
    A& operator ++ (int) {
        A copy(this->x);
        ++x;
        return copy;
    }
    
    friend std::ostream& operator << (std::ostream& os, const A& right){
        os << right.x;
        return os;
    }
    
private:
    int x;
};

int main(){
    C c1(1);
//    B b1(3);
//    c1 += b1;
//
    std::cout << c1.info(5) << c1.inf() << c1.x << c1.i << "\n";
    
//    Dog d1(true);
//    Pet& ref = d1;
//    ref.noise();
    
//    Corgi c1(true);
//    Dog& ref = c1;
//    ref.noise();
    
    A a1(3);
    std::cout << a1++ << " " << a1;
    
    return 0;
}
