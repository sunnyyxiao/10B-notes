//
//  fundamentals3.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 1/12/24.
//

#include <iostream>
#include <cmath>
#include <vector>
#include <array>
#include <set>
#include <unordered_set>
#include <cmath>

using namespace std;

void printArrayWrong(int a[]){
    cout << sizeof(a) << endl;
}

//C-style arrays
void printArray(int *p, size_t N){
    cout << sizeof(p)/N << endl;
}


void printArray(const array<int, 4>& a){
    for (size_t i = 0; i < 4; i++){
        cout << a[i] << " " << &a[i] << endl;
    }
}

/*
 Customer class
 - name (string), purchases (vector), spend(int)
 - two constructors
 - purchase function, takes in string and price, adds item to purchases and price to spend, purchase function should be only way that a customer's record is updated!
 */
class Customer{
private:
    vector<string> purchases;
    int spend;
    
public:
    string name;
    Customer():name("Test"),spend(0),purchases(){}
    Customer(string _name, int _spend, vector<string> _purchases):name(_name),spend(_spend),purchases(_purchases){}
    void see_spend() const {
        cout << spend << endl;
    }
    void see_purchases() const {
        for (size_t i = 0; i < purchases.size(); i++){
            cout << purchases[i] << " ";
        }
        cout << endl;
    }
    void purchase(string item, int cost){
        purchases.push_back(item);
        spend += cost;
    }
    
};


int main(){
    /*
     DATA STRUCTURES AND C++ CONTAINERS
     A data structure is an abstract set of rules for how to organize data. A data structure is designed to help with the task of efficiently storing and or searching data, but there are generally tradeoffs, for example a data structure might be efficient to search but inefficient to mutate/change or visa versa.
     
     C++ containers are holder objects that store collections of other objects, like ints, doubles, or strings or even custom types. C++ containers thus represnt particular implementations of data structures in C++.
     */
    
    {
        cout << "C-style arrays: " << endl;
        /*
         These are a hangover from C. They essentially consist of a block of memory with a constant size that must be known before runtime
         - data is stored contiguously
         - must have constant size
         - indexed
         - size of array (number of elements) can be inferred using length
         - cannot be reallocated to a different memory location during runtime
         - decay to a pointer when passed to a function, so also need to pass size of array
         */
        
        //Declare array size in advance
        const size_t N = 4;
        
        //Declare but don't initialize
//        int a[N];
        
        //Declare an initialize on one line
        int b[N] {1,2,3,4};
        //int b[] {1,2,3,4};
        
        //Use for loop to pass through array. Print out the memory locations - what do you observe?
        int* p = b;
        for (size_t i = 0; i < N; i++){
            cout << b[i] << " " << b + i << " ";
            //going up 4 bytes with each one
            
            //using pointer to print same thing
            cout << *(p+i) << " " << (p+i) << endl;
        }
        
        //trying to print size of array, but this actually prints out sizeof for pointer
        printArrayWrong(b);
        
        //print array correct
        printArray(b,N);
        
    }
    
    {
        /*
         Standard library arrays: like C-style arrays but with way more member functions! Can also be passed by value to functions rather than decayed to a pointer
         */
        cout << "Standard library arrays: " << endl;
        
        const size_t N = 4;
        array<int, N> a = {4,2,1,3};
        //std container operations supported like sorting
        //.begin and .end return pointers to the start and end of an array
        sort(a.begin(),a.end());
        printArray(a);
        
    }
    
    {
        /*
         Standard library vectors: these ae like arrays but their size can be changed by relalocating to a different memory location.
         - capacity is the max number of objects that can be stored in the vector's current location
         - size is the number of objects currently stored in the vector
         */
        cout << "Standard library vectors: " << endl;
        
        //Declare and initialize a vector
        vector<int> v1;
        cout << v1.size() << "\n";
        
        cout << &v1[0] <<"\n";
        
        for (int i = 1; i < 8; i++){
            v1.push_back(i);
            cout << v1.capacity() << endl;
            for (size_t i = 0; i < v1.size(); i++){
                cout << v1[i] << " " ;
            }
            cout << endl;
        }
        
        cout << &v1[0] << "\n";
    }
    
    {
        cout << "Standard library sets: " << endl;
        /*
         Sets: unordered and ordered
         Sets are not indexed and their elements aren't stored contiguously typically. Can't use a standard indexed for loop, instead need to use a range based for loop. Under the hood we still use pointers to traverse the container, but we can't just increment by the size of the type! We'll range based for loops in more detail later on, but for now just remember the syntax essentially defines a reference to container. Sets are stored in a very particular way so to mutate them we have to do so through methods.
         */
        
        //ordered set stores elements in terms of least to most memory (ordered by the < operator)
        set<int> s1 = {1,4,3,4,2,3,1,2,3,4};
        
        //stores in form of last in, first out
        unordered_set <int> s2 {4,2,3,1,2,3,2,3,1};
        
        //Note that just like a set in math the elements of a set are unique
        
        //Sets and unordered sets are ordered by the '<<' operator
        for (const int& item: s1){
            cout << item << endl;
        }
        
        for (const int& item: s2){
            cout << item << endl;
        }
        cout << endl;
    }
    
    {
        /*
         Classes in C++ support OOP.
         - allow you to define custom types which bundle together variables and functions under one name
         - class members can be accessed via the member operator '.'
         - public members can be accessed in main, but private only inside member function definitions
         - const instances of a class can only call member functions marked const, therefore a member function which doesn't mutate any member variables should be marked const
         */
        cout << "Classes: " << endl;
        
        Customer c1;
        c1.see_spend();
        c1.see_purchases();
        c1.purchase("oranges",1);
        c1.see_spend();
        c1.see_purchases();
        c1.purchase("kiwis",150);
        c1.see_spend();
        c1.see_purchases();
        
        
    }
    return 0;
}
