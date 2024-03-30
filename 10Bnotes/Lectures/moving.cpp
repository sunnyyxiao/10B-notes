//
//  moving.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 2/26/24.
//

#include <iostream>
#include <utility>
#include <vector>


namespace detail {
    template <class T> struct value_category      { static constexpr char const* value = "prvalue"; };
    template <class T> struct value_category<T&>  { static constexpr char const* value = "lvalue"; };
    template <class T> struct value_category<T&&> { static constexpr char const* value = "xvalue"; };
}

#define PRINT_VALUE_CAT(expr) std::cout << #expr << " is a " << ::detail::value_category<decltype((expr))>::value << '\n';


struct A{
    A(int _i, double _d):i(_i), p(new double(_d)){std::cout<<"Parameterized constructor called!\n";}
    A():i(0), p(new double(0)){std::cout<<"Default constructor called!\n";}
    A(const A& a):i(a.i), p(new double(*(a.p))){std::cout<<"Copy constructor called!\n";}
    ~A(){std::cout<<"Destructor called!\n"; delete p;}
    A& operator=(const A& right){
        std::cout<<"Copy assignment operator called!\n";
        i = right.i;
        if (right.p!=nullptr){p = new double(*(right.p));}
        else{p = nullptr;}
        return *this;
    }
    friend A operator + (const A& left, const A& right){
        double l = 0;
        double r = 0;
        if (left.p != nullptr){l = *left.p;}
        if (right.p != nullptr){r = *right.p;}
        A temp(A(left.i + right.i, l+r));
        return temp;
    }
    // integer data member variable on the stack
    int i;
    // pointer data member, points to a double on the heap
    double* p;
};



struct B{
    //Parameterized and default constructor and destructor
    B(int _i, double _d): i(_i), p(std::make_shared<double>(_d)){std::cout << "Parameterized constructor of B called with i = " << i << ", *p = " << *p << std::endl;}
    
    B():i(0),p(nullptr){std::cout << "Default constructor of B called" << std::endl;}
    
    ~B(){std::cout << "Destructor of B called!\n";}
    
    //Copy constructor and copy assignment operator (make both deep)
    B(const B& r): i(r.i), p(std::make_shared<double>(*(r.p))){std::cout << "Copy constructor of B called with i = " << i << ", *p = " << *p << std::endl;}
    //Shallow copying would indicate *p = *(r.p), but in this case, we are using deep copy
    B& operator = (const B& r){
        std::cout << "Copy assignment of B called!\n";
        i = r.i;
        if (r.p!=nullptr){
            p = std::make_shared<double>(*(r.p));
        }
        else{p = nullptr;}
        return *this;
    }
    
    //Move constructor and move assignment operator
    /*
     Move constructor creates an object by taking over the resources of a temporary object
        - parameter is an rvalue reference
        - copy small objects on the stack
        - swap pointers to objects on the heap
     */
    B(B&& r):i(r.i), p(nullptr){
        std::swap(p, r.p);
        std::cout << "Move constructor of B called with i = " << i << ", *p = " << *p << std::endl;
    }
    
    B& operator = (B&& r){
        i = r.i;
        std::swap(p,r.p);
        std::cout << "Move assignment of B called!\n";
        return *this;
    }
    
    int i;
    std::shared_ptr<double> p;
};


int main(){
    
    // Motivating the move assignment operator
    {
        std::cout << "Demonstration: copy assignment\n";
    // We saw last time that copying could in theory be quite inefficient: in particular, we don't want to construct a temporary object, and then copy the contents of this temporary object to a more permanent one. One way to avoid this is by the compiler carrying out copy elisions, however this occurs only in particular settings. In particular recall the following admittedly somewhat contrived example.
        A a1(3,2.5); // Parameterized constructor called to create a1
        a1 = A(); // Default constructor called to create temporary object, copy assignment used to copy over contents from temporary object. Not efficient!
        std::cout<< "Do some stuff...\n";
    /*
     In particular the line a1=A() does the following
     1) deep copies or clones the resource from the temporary returned by the constructor to a1
     2) destructs the resource held by a1 originally, i.e., the double 2.5 in this case!
     3) destructs the temporary, releasing the resource held by the temporary
     
     (Note final destructor call is for a1. We don't see destructor call for temporary object.)
     
     The idea of moving is to essentially swap 'pointers', so that the temporary object now owns double 2.5 on the heap and a1 now owns the double 0 on the heap. That way when the temporary is destroyed the double 2.5 is deleted as well!
     */
    }
    
    // Demonstration of move assignment operator
    {
        std::cout<<"\nDemonstration: move assignment\n";
        B b1(3,2.5); // Parameterized constructor called
        b1 = B();
        std::cout<< "Do some stuff...\n";
        /*
         The line b1 = B() does the following
         - First the default constructor is called to create a temporary type A object
         - Then the move assignment operator is called, which copies the integer value on the stack and swaps the pointers
         - Then the temporary object is deleted which deallocates the resource for the 2.5 double on the heap
         - Note second destructor call at the bottom is for b1 when we exit this block scope
         
         Compared to the copy assignment we didn't have to copy the double on the heap. For a double this isn't a big deal, in fact the copy assignment might even be more efficient in certain cases... But imagine instead of having a single double we had 100000 doubles!
         */
        
        /* Question: why did b1 = B() call the move constructor not the copy constructor? Recall that a function which does not return an lvalue or rvalue reference returns a prvalue (at least I'm not aware of any counterexamples). Indeed we can check this.
         */
        PRINT_VALUE_CAT(B()); // B() is a prvalue which is a type of rvalue
        /*
        - For the copy assignment operator, the argument-to-parameter assignment is
              const B& p = B();
          This is acceptable as anything can bind to a const lvalue reference
        - In the second case, the argument-to-parameter assignment would be
              B&& p = B();
         This is acceptable as rvalues can bind to rvalue references
       So both are acceptable, but an r-value reference is a better fit for referencing an r-value, and so move assignment operator is used instead.
         */
    }
    
    // Motivating the move constructor
    {
        std::cout << "\nDemonstration: copy constructor in vector\n";
        // To motivate the move constructor lets consider a vector of A objects. Note we aren't reserving any space so everytime we update the vector the new, larger vector is copied now to a new location.
        std::vector<A> As;
//        As.reserve(10);
        As.push_back(A(1,1.1));
        std::cout << "do stuff ... \n";
        As.push_back(A(2,2.2));
        std::cout << "do stuff ... \n";
        As.push_back(A(2,2.2));
        std::cout << "do stuff ... \n";
        As.push_back(A(2,2.2));
        /*
         Every time we use push_back we have to copy the existing contents to a new location. Indeed the steps involved with push_back are as follows.
         - First call parameterized constructor to create temporary A object
         - Then copy contents of temporary object to new vector location
         - Copy over the rest of the old vector
         - Destroy contents of old vector
         */
        std::cout << "do stuff ... \n";
    }
    
    
    // Move constructor in a vector
    {
        std::cout << "\nDemonstration: move constructor in vector\n";
        // To motivate the move constructor lets consider a vector of A objects.
        std::vector<B> Bs;
        Bs.reserve(10); // This is a way of reserving the size in memory in advance so don't have to move / copy each time we add an element. If we don't specify this though could end up doing a lot of copies if you don't define a move constructor!
        Bs.push_back(B(1,1.1));
        
        std::cout << "do stuff ... \n";
        Bs.push_back(B(2,2.2));
        
        std::cout << "do stuff ... \n";
        Bs.push_back(B(3,3.3));
        /*
          Now the steps involved with each push_back call are as follows.
         - First call parameterized constructor to create temporary B object
         - Then the move constructor is called to move the contents of the temporary object into the new element in the vector
         - Copy is called for all the elements in the old vector
         - Destructor is used on all elements in the old vector
         */
        std::cout << "do stuff ... \n";
    }
    
    
    return 0;
}

