//
//  rvalue_refs_value_categories.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 2/23/24.
//

#include <iostream>
#include <vector>

/*
 Copying objects is expensive from a memory perspective, but also in terms of taking up CPU time.
 
 Lvalue references are aliases for existing variables and are useful in facilitating pass by reference semantics. Instead of copying an object into a new local variable inside a function scope, we pass the location of an outside object into the local function scope.

 A temporary object is also unnamed and is created by the compiler to store a temporary value. Literals are an example of a temporary type, the return from a function is also a temporary type.
 
 An rvalue reference is declared like an lvalue reference but with an extra &, e.g. int&& r2 = 3 declares and initializes an rvalue reference. "Extends the lifespan" of otherwise temporary objects, such as x+2. Non-const rvalues can also be reassigned to a different literal, such as r2 = 6;.
 
 Expressions in C++ are simply sequences of operators (+, -, /, written functions) and operands (variable names, function calls, literals, constants). Simply calling 'x' is also considered an expression, as you are accessing the value of x.
 
 Type: the type of object outputted from the evaluation of an expression (int x = 2, or x*2 where x is an int -> integer type).
 
 The value category of an expression answers "how long will the output arising from the evaluation of an expression last?" It tells us whether the output arising from evaluating an expression is temporary or more permanent. It DOES NOT refer to the value of the outcome of the evaluation of the expression.
 
    L-value expressions: used to designate objects which are stored in memory and locatable via their memory address. If we are allowed to append the & memory access operator to the start of an expression, then it is an l-value expression.
 
    P-value expressions: used to designate temporary objects, for example numeric, character, or string literals, which are stored in a different type or place in memory and only a short time. We can't use the & operator to access where they are stored.
 
    X-value (expiring) expressions: these are expressions used to designate objects which are lvalues on the cusp of expiring. Main example would be the outcome of a move command.
 
 Anything can bind to a const lvalue reference, but only lvalues can bind to non-const lvalue references.
 Only rvalues can bind to rvalue references.
 */

namespace detail {
    template <class T> struct value_category      { static constexpr char const* value = "prvalue"; };
    template <class T> struct value_category<T&>  { static constexpr char const* value = "lvalue"; };
    template <class T> struct value_category<T&&> { static constexpr char const* value = "xvalue"; };
}

// Will prove useful
#define PRINT_VALUE_CAT(expr) std::cout << #expr << " is a " << ::detail::value_category<decltype((expr))>::value << '\n';

// needed later
int my_max(int i, int j) {
    // the expressions i and j are l-value expressions
    // We can take the address of i and j
//    int* pi = &i;
//    int* pj = &j;
//    std::swap(pi, pj); // to silence warnings

    if (i > j) {
        return i;
    }
    return j;
}

// needed later
const int& pass_along_1(const int& i) { return i; }
const int& pass_along_2(const int& i) { return i; }

// needed later
int& rf(int& i) { return i; }
int  vl(int  i) { return i; }

// needed later
void foo(int& r){std::cout << "Foo 1 used\n";}  // #1
void foo(int&& r){std::cout << "Foo 2 used\n";} // #2


int main(){
    
    {
        //Lvalue expression since r is an lvalue
        int&& r = 6;
        int& s = r;
        
        std::cout << &r << " " << &s << "\n";
    }
    
    /*
     EXPRESSION TYPES:
     An expression is evaluated, i.e., produces something. The type of an expression corresponds to the type of the object which is produced by it.
     */
    
    {
        int i = 0; // an int
        int i2 = 1;
        double d = 0; // a double
        const int* p = &i; // a pointer to const int
        double& r = d; // an l-value reference to double
        
        p = &i; r = d; //silence warnings
        
        std::string s("0"); //a std::string
        std::vector<int> v(8); //a std::vector of ints
        
        std::vector<double>().size(); // a size_t
    }
    
    
    /*
     L values
     Recall an l-value is an object to which we can apply &. Often this means it can be assigned to (unless const).
     
     Variable names are examples of lvalues, as are for instance expressions involving indexing as follows
     - if v is a vector and i < v.size(), then v[i] is an l-value
        *v.size() itself is not an lvalue
     - if s is a string and i < s.size(), then s[i] is an l-value
     - string literals
     */
    
    {
        int i = 0;
        double d = 0;
        
        const int* p = &i; //p is an l-value (&i is not)
        double& r = d; //r is an l-value
        
        p = &i; r = d; //silence warnings
        
        std::string s("0");
        std::vector<int> v(8);
        
        s[0]; //l-value
        v[4]; //v[4] is an l-value
        std::cout << &"l-value"; //"l-value" is an l-value
        //string literals are l-values
        
        std::cout << std::endl;
        
    }
    
    /*
     L-values are assigned a place in memory. This means they are more permanent, but they can still go out of scope! Anything that is not an lvalue is an r value.
     */
    
    /*
     R-VALUES
     
     Often "expire" after a given line of execution. The given line of execution could involve multiple function calls, and r-value's lives can also be extended through r-value references.
     */
    
    /*
     PR-VALUES
     Example of a numeric literal or unnamed temporary object like std::vector<int>(8) or std::string("0") as they are not assigned to anything.
     
     A pr-value does not have an addressable location in RAM, perhaps being a value returned from during a computation.
     */
    {
        int i = 0;                // i is an l-value but 0 is an pr-value
        double d = 8.8 - 0.8;     // 8.8 - 0.8 is an pr-value

        const int* p = &i;        // &i is an pr-value
        double& r = d;            // r and d are l-values

        p = &i; r = d; // just to silence warnings

        std::string s;            // s is an l-value
        s = std::string("0");     // std::string("0") is an pr-value

        std::vector<int> v;       // v is an l-value
        v = std::vector<int>(8);  // std::vector<int>(8) is an pr-value
    }
    
    /*
     X-VALUES
     They are a little closer to l-values than pr-values, but are considered r-values.
     
     - Used to be an l-value but became an r-value, being cast from a more permanent state to a less permanent state.
        std::move is a function which accomplishes this
     - Used to be a pr value but due to member access got promoted to an x-value.
     
     An x-value does exist in memory, even if the existence is only temporary. However, we can't ask for its address directly.
     */
    {
        int i = 8;
    //    int& r5 = 9;
        
    //    int&& r1 = i; //cannot bind an r-value reference to an l-value
        
        int&& r1 = std::move(i); //std::move(i) is an x-value, thus an r-value
        
    //    int&& r2 = r1; //cannot bind an r-value reference to an l-value
        int&& r2 = std::move(r1); //std::move(r1) is an x-value, thus an r-value
        
        std::cout << i << ' ' << r1 << ' ' << r2 << std::endl;
        std::cout << &i << ' ' << &r1 << ' ' << &r2 << std::endl;
        
        std::string name("Rafa21"); //name is an l-value
        std::move(name); //an x-value expression
        
        std::string("dynamic").substr(4);
        //Ordinarily, std::string("dynamic") would be pr-value. Because member access was used, it is promoted to an x-value. The whole expression is a pr-value.
        
    }
    
    /* WHAT DOES TEMPORARY REALLY MEAN?
     Ok so rvalues are sort of temporary, but what does this really mean?
     Consider int my_max(int i, int j).

     When the function is called, during its execution i and j are l-values: However, these variables only exist for the duration of the function call. In this sense, they're less "permanent" than you might expect. However, to every other object inside the function call they seem pretty permanent!
    */
    {
        std::cout << my_max(-18, -8) << std::endl;
    }
    
    
    /*
     In particular, remember that an object designated by an r-value will exists at least as long as it takes to evaluate the expression in question.
    */
    {
        // the expression 8 is an rvalue, the expression r_c is an lvalue
        const int& r_c = 8;
        // the temporary object 18 lives long enough to initialize 'passed_along_to_here'
        int passed_along_to_here = pass_along_2(pass_along_1(18));
        std::cout << passed_along_to_here << std::endl;
        // the 8 we created will exist until the end of this scope
        std::cout << &r_c << std::endl;
    }
    
    // --------------------------------------------------------
    /*
     FUNCTION CALLS AND VALUE CATEGORIES
     A function call is:
      - an l-value if the return type is an l-value reference type,
      - an x-value if the result type is an r-value reference type,
      - a pr-value in most other cases (ignoring returning functions).
    */
    // --------------------------------------------------------
    {
        int i = 8;
        int& lr = rf(i); // rf(i) is an l-value since rf returns an l-value reference
        int&& rr = vl(i); // vl(i) is a pr-value since vl returns by value (vl does not return an r-value reference)
        
        // Don't get confused here, rr is an rvalue reference, but the expression is an rr is an lvalue
        std::cout <<  i << ' ' <<  lr << ' ' <<  rr << std::endl;
        std::cout << &i << ' ' << &lr << ' ' << &rr << std::endl;
    }
        
    
    /*
     R-VALUE REFERENCES
     An r-value reference (declared with &&) can only bind to r-values. They can help make various constructions and assignments more efficient (move semantics).

     The expression of an r-value references will have names and so they are themselves l-values. Creating an r-value reference to an r-value will extend the lifetime of the r-value just like for l-value references to const.
    */
    {
        int&& r1 = 8;                         // 8 is an r-value
        // r1's type is r-value reference to int.
        // r1's value category is l-value!!

        int&& r2 = r1 + 10;                   // r1 + 10 is an r-value
        // r2's type is r-value reference to int.
        // r2's value category is l-value!!

        std::string&& r3 = std::string("0");  // std::string("0") is an r-value
        //"0" is an l-value
        // r3's type is r-value reference to std::string.
        // r3's value category is l-value!!

        std::cout <<  r1 << ' ' <<  r2 << ' ' <<  r3 << std::endl;
        std::cout << &r1 << ' ' << &r2 << ' ' << &r3 << std::endl;
    }
    
    
    /*
     Understanding the value category of an expression is important as certain combinations of assignmet from an expression on the left to an lvalue/ rvalue reference on the right are not permitted!
     */
    {
        int i = 2;
        // An lvalue or rvalue can bind to a const lvalue reference
        const int& r1 = 2; // rvalue expression rhs
        const int& r2 = i; // lvalue expression on rhs
        
        // Only lvalues can bind to non-const lvalue references
//        int& r3 = 2; // rvalue expression rhs
        int& r4 = i; // lvalue expression on rhs
        
        // Only rvalues can bind to rvalue references.
        int&& r5 = 2; // rvalue expression rhs
//        int&& r6 = i; // lvalue expression on rhs
        
        // A a practical example, which foo function will be used?
        int&& r = 42;
        
        //r itself is an lvalue --> uses foo1
        foo(r);
        foo(0);
        // What!? Ok so only an lvalue can be bound to a non-constant lvalue reference, therefore when we pass in an lvalue reference Foo 1 is used. Also, as only an rvalue can be bound to an rvalue reference, when we pass as argument 0, which is an rvalue, then it cannot be assigned to the Foo with the lvalue reference parameter, i.e., foo 1. But int&& r = 0 is allowed so Foo2 is used instead.
    }
    
    
    // We can check the type categories of certain expressions (not declarations) using the following command defined at the top. Not to be trusted in all cases.
    {
        std::string s = "abc";
        PRINT_VALUE_CAT(move(s));
    }
    return 0;
}

