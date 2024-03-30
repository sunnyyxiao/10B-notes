//
//  smart_pointers_usage.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 2/16/24.
//

#include <iostream>

struct A{
    A(int _a):a(_a){std::cout << "constructor of A object with a=" << a << " called \n";}
    ~A(){std::cout << "destructor of A object with a=" << a << " called \n";}
    void greet(){std::cout << "Hi!\n";}
    int a;
};

std::unique_ptr<A> get_heap_A(){
    std::cout << "Enter an integer value: ";
    int x;
    std::cin >> x;
    return std::make_unique<A>(A(x));
    //std::unique_ptr<A>(new A(x));
}

void addA(int i, std::unique_ptr<A>& b){
    b->a += i;
    if (b->a > 10) {
        std::cout << "Deleting unique pointer\n";
        b.reset();
    } else return;
}
/*
 Exercise: shared pointers are primarily used when more than one object should have ownership over another object. Write a struct for a class B object, containing a pointer to a type A object on the heap. Multiple class B objects should be able to own the same A object. Make sure no memory leaks occur.
 - should have member variables a double b and a pointer sp (choose which type) to an A object
 - constructor should accept an integer with which to create an A object on the heap and a double to initialize b
 - destructor should print a message including value of double member
 - member function reset which takes an input argument and uses it to reset the pointer member
 */
struct B{
    B(int i, double d):sp(std::make_shared<A>(A(i))), b(d) {}
    ~B(){std::cout << "destructor of B object with b=" << b << " called\n";}
    void reset(int x){
        sp.reset(new A(x));
    }
    double b;
    std::shared_ptr<A> sp;
};


int main(){
    
    // ----------------------------------------------
    // UNIQUE POINTERS: https://en.cppreference.com/w/cpp/memory/unique_ptr
    // ----------------------------------------------
    //Sits on heap or stack, and has full ownership of something on the heap, no other smart pointers can be bound to the object
    
    std::cout << "UNIQUE POINTERS\n";
    
    std::cout << "Creation and initialization: 1\n";
    {
        //It is possible to declare without initializing a smart pointer
        std::unique_ptr<int> up1;
        up1 = std::unique_ptr<int>(new int(8));
        //The above command provides an integer on the heap to the constructor for a unique pointer to an integer type. We can also reassign up1 to point at a new integer
        std::cout << *up1 << "\n";
        
        //below is not a viable way, because as up1 is a unique pointer, we must delete the object it is bound to before reassigning
//        up1 = new int (9);
        //okay, but better to use another method
        up1 = std::unique_ptr<int> (new int(9));
        std::cout << *up1 << "\n";
    }
    
    std::cout << "Creation and initialization: 2\n";
    
    {
        //One remark with this line we have just one destructor call at the end
        std::unique_ptr<A> up1 = std::unique_ptr<A>(new A(5));
        
        //Make_unique duplicates the object once it has been created and destroys the original so we get two destructor calls! We will gain some insight as to why in the following lectures where we study move and copy. Safer from an exception handling viewpoint
        std::unique_ptr<A> up2 = std::make_unique<A> (A(10));
        
        std::cout << up2 << "\n";
    }
    //up1 and up2 go out of scope after this block ends
    
    
    std::cout << "\nUsage and operations:\n";
    //Usage and Operations
    {
        std::unique_ptr<A> up1 = std::make_unique<A>(A(7));
        
        //The usual pointer operators are overloaded so that they apply to the underlying raw pointer. This applies to unique and shared pointers
        std::cout << up1 << "\n";
        up1->greet();
        std::cout << up1->a << "\n";
        
        //Using reset reassigns a unique pointer to have ownership over a new object. Note destructor is called on the old object
        up1.reset(new A(9));
        std::cout << up1->a << "\n";
        
        //reset does the same thing as reassigning directly to std::make_unique
        up1 = std::make_unique<A>(A(10));
        std::cout << up1-> a << "\n";
        
        //It is not possible to assign one unique pointer to another as ownership is unique
//        std::unique_ptr<A> up2 = up1;
        
        
        //The .get() method returns the underlying raw pointer. pA is now bound to the the object on the heap that up1 is bound to. This also applies to shared pointers!
        A* pA = up1.get();
        std::cout << "raw pointer: " << pA->a << "\n";
        
        //Note that a raw pointer has no ownership of an object, so we can attach raw pointers to objects with unique pointers. This is not typically considered good practice and should only be temporary.
        
        //It is also possible to release ownership of an object, .release() returns a raw pointer to the managed object. The control block is deallocated as up1 is now unbound to the object on the heap and is bound to a nullptr.
        A* p1 = up1.release();
        
        if (up1.get() == nullptr){
            std::cout << "up1 now points at nullptr, no longer owns the object\n";
        }
        
        delete p1;
        p1 = pA = nullptr;
    }
    
    
    //Exercise 1: write a function which asks a user for an integer value then uses it to construct an A object on the heap. The function should return a pointer to the A object after executing in such a fashion that memory leaks are always avoided
    {
        std::cout << "\nEXERCISE 1\n";
        //Even though we don't actually assign the returned pointer a variable in the program the object on the heap is still deleted!
        
        std::unique_ptr<A> up1 = get_heap_A();
        std::cout << "A version of the A object with a " << up1->a << " is still available!\n";
    }
    
    //Exercise 2: write a function that takes a unique pointer to an A object and an integer and adds them together. As a follow up how would you adjust this function so it deletes the A object if its value is say >10?
    
    {
        std::cout << "\nEXERCISE 2\n";
        std::unique_ptr<A> up1 = std::make_unique<A>(A(10));
        addA(2,up1);
        if (up1.get() != nullptr){
            std::cout << up1->a << "\n";
        } else std::cout << "up1 has been deleted\n";
    }
    
    //SHARED POINTERS
    {
        std::cout << "\nSHARED POINTERS: \n";
        
        std::cout << "Creation and initialization\n";
        
        {
            // Analagous to unique pointer case, you should use make_shared to construct an A object.
            std::shared_ptr<A> sp1 = std::make_shared<A>(A(10));
        }
        std::cout << "\nShared ownership\n";
        {
            // Shared pointers allow a shared ownership structure, therefore it is possible to assign shared pointers to other shared pointers (executes a copy construction which we will see soon) which is not the case for unique pointers
            std::shared_ptr<A> sp1 = std::make_shared<A>(A(10));
            std::shared_ptr<A> sp2 = sp1;
            std::shared_ptr<A> sp3 = sp2;
            
            // As we saw last time we can access a count of the shared pointers using use_count()
            std::cout << sp2.use_count() << "\n";
        }
        
        std::cout << "\nObject deletion\n";
        {
            // An object is only destroyed when it all of its shared pointers go out of scope.
            std::shared_ptr<A> sp1 = std::make_shared<A>(A(12));
            {
                std::shared_ptr<A> sp2 = std::make_shared<A>(A(15));
                std::shared_ptr<A> sp3 = sp1;
                std::cout << "Exiting inner scope...\n";
            }
            std::cout << "...exited inner scope!\n";
        }
        
        std::cout << "\nUseful member functions:\n";
        {
            // shared pointers do not have a release member function
            
            // Like reset for unique pointers, reset allows a new object assignment of a new object to a shared pointer.
            std::shared_ptr<A> sp1 = std::make_shared<A>(A(1));
            std::shared_ptr<A> sp2 = std::make_shared<A>(A(2));
            std::shared_ptr<A> sp3 = sp1;
            
            sp2.reset(new A(3));
            sp3.reset(); // resets as nullptr
            // Observe A object with 2 destroyed first before 3 or 1!
        }
        
        
        /*Exercise: shared pointers are primarily used when more than one object should have ownership over another object. Write a struct for a class B object, containing a pointer on the stack to a type A object on the heap. Multiple class B objects should be able to own the same A object. Make sure no memory leaks occur.
         - should have member variables a double b and a pointer sp (choose which type) to an A object
         - constructor should accept an integer with which to create an A object on the heap and a double to initialize b
         - destructor should print a message including value of double member
         - member function reset which takes an input argument and uses it to reset the pointer member
         */
        std::cout << "\nExercise for shared pointers:\n";
        {
            // Uncomment when ready
            B b1(1,3.72);
            std::cout << b1.sp.use_count() << "\n";
            B b2 = b1;
            std::cout << b1.sp.use_count() << "\n";
            B b3(21, 19.14);
    
            b1.reset(4);
            b2.reset(5);
        }
        
        
        
        // ----------------------------------------------
        // WEAK POINTERS: https://en.cppreference.com/w/cpp/memory/weak_ptr
        // ----------------------------------------------
        /* Weak pointers have two uses:
         - act like observers, and only take ownership typically temporarily when access to the object is required by conversion to a shared_ptr
         - useful for breaking cyclic dependency between shared pointers
         */
        std::cout << "\nWEAK POINTERS\n";
        
        std::cout << "\nCreation, initialization and ownership 1: \n";
        {
            // Weak pointers are generally constructed from shared pointers
            std::weak_ptr<A> wp1 = std::make_shared<A>(A(10));
            // Note conversion of shared pointer to weak pointer means there are no pointers which actually own the A object. In this example it therefore is immediately destroyed! This we can check with the boolean expired() method.
            std::cout<< std::boolalpha << "Object has expired? " << wp1.expired() << "\n";
        }
        
        std::cout << "\nCreation, initialization and ownership 2: \n";
        {
            //In this example we create a shared pointer, sp1, and then we copy it over to wp1
            std::shared_ptr<A> sp1 = std::make_shared<A>(A(10));
            std::weak_ptr<A> wp1 = sp1;
            std::cout<< std::boolalpha << "Object has expired? " << wp1.expired() << "\n";
        }
        
        std::cout << "\nObject cannot be accessed through weak pointer: \n";
        {
            std::shared_ptr<A> sp1 = std::make_shared<A>(A(10));
            std::weak_ptr<A> wp1 = sp1;
            // Following result in errors:
    //        std::cout << wp1->a << "\n";
    //        wp1->greet();
        }
        
        
        std::cout << "\nTo access an object through a weak pointer need to create, at least temporarily a shared pointer: \n";
        {
            std::shared_ptr<A> sp1 = std::make_shared<A>(A(4));
            std::weak_ptr<A> wp1 = sp1;
            std::cout << wp1.lock() << &sp1;
            
            {
                // Lock returns a shared pointer
                std::shared_ptr<A> sp2 = wp1.lock();
                std::cout << sp2->a << "\n";
                sp2->greet();
                // sp2 is temporary here, only available inside this scope for instance.
            }
        }
    }
    
    return 0;
}
