//
//  inheritancetest.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 1/30/24.
//

#include <iostream>
using namespace std;

////Will always call default constructor
//class Vehicle{
//public:
//    Vehicle(){cout << "This is the default\n";}
//    Vehicle(string s) {cout << "This is a Vehicle\n"; }
//};
//
//class fourWheeler : public Vehicle{
//public:
//    fourWheeler():Vehicle("base"){cout << "This is a Four-Wheeler\n";}
//};
//
//class Car : public fourWheeler {
//public:
//    Car(int a):fourWheeler(){cout << "This is a Car\n";}
//};
//
//int main(){
//    fourWheeler wheel;
//    return 0;
//}

class Parent_a{
public:
    Parent_a():a(1){}
    void set_a(int a_v){a = a_v;}
    int get_a(){return a;}
    virtual int get_b(){}
    virtual int get_c(){}
private:
    int a;
};

class Child_b: public Parent_a{
public:
    Child_b():b(2){}
    void set_b(int b_v){b= b_v;}
    int get_b(){return b;}
private:
    int b;
};

class Child_c: public Child_b{
public:
    Child_c():c(3){}
    void set_c(int c_v){c= c_v;}
    int get_c(){return c;}
private:
    int c;
};

int main(){
    Parent_a pa;
    Child_b cb;
    
    cout << "Parent_a.a: " < pa.get_a() << endl;
    cout << cb.get_b();
    cout << cb.get_a();
}
