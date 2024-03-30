//
//  smart_pointers.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 2/14/24.
//

#include <iostream>

/*
 Issues with raw pointers:
 - unclear level of ownership over the objects they point at (the declaration of a raw pointer says nothing in this regard which was an issue when we created heap objects; if not explicit in deleting an object we risk memory leaks!
 - even if it owns an object it is often not clear how said object should be destroyed (from the declaration of a pointer it is not clear whether the pointer is pointing at an array of objects or at a single object)
 - hard to check whether deletion occurs exactly once along each possible execution path (in particular if delete is called twice, this causes errors so for safety we manually had to assign raw pointers to nullptr)
 - hard to tell if it is dangling (dangling pointers point at memory no longer allocated to hold the object the pointer was supposed to point at)
 */

/*
 Smart pointers:
 These are classes wrapped around raw pointers. They are safer and easier to use than raw pointers when it comes to binding them to objects on the heap. The only real downside of smart pointers over raw pointers is their size and some small additional computational overheads. There are three types of smart pointers, so one also needs to pick the correct type for the job at hand.
 
 General principles:
 - should typically be stored on the stack
 - should be bound to objects on the heap, not the stack, as memory management on the stack is already handled by a different system which we have discussed
 
 Three types of smart pointers:
 - unique pointers, std::unique_ptr are the sole owners of an object on the heap! Lightest weight smart pointers
 - shared pointers, std::shared_ptr own an object in heap memory and in addition tracks the number of other shared_ptr objects referencing the same object. As the name suggests, unlike a unique_ptr a shared_ptr object can share ownership of an object on the heap with other shared_ptr objects
 - weak pointers, std::weak_ptr do not take ownership of an object but act as an observer. In particular, weak pointers do not participate in the ownership/reference counting involved with the decision to delete a heap object or extend its lifetime. Weak pointers are mainly used to break the circular dependency that shared pointers can sometimes create.
 
 */

struct A{
    A(){}
    ~A(){std::cout << "destructor of A called \n";}
};

struct B{
    B(){}
    ~B(){std::cout << "destructor of B called \n";}
};

struct C{
    C():pA(new A), b(B()), i(1){}
    A* pA;
    B b;
    int i;
    //Note when we delete a C object we do not automatically delete the A object, only the pointer to the A object! For this reason we need to explicitly ask to destroy A inside the destructor
    ~C(){
        std::cout << "destructor of C called \n";
        delete pA; //see what happens when this is commented out
    }
};

struct Dog1;
struct Human1;

struct Dog1{
    std::shared_ptr<Human1> human;
    ~Dog1(){std::cout << "Destructor for dog1 called \n";}
};

struct Human1{
    std::shared_ptr<Dog1> dog;
    ~Human1(){std::cout << "Destructor for human1 called \n";}
};

struct Dog2;
struct Human2;

struct Dog2{
    std::shared_ptr<Human2> human;
    ~Dog2(){std::cout << "Destructor for dog2 called \n";}
};

struct Human2{
    std::weak_ptr<Dog2> dog;
    ~Human2(){std::cout << "Destructor for human2 called \n";}
};



int main(){
    {
        std::cout << "Class C object on the stack.\n";
        C c;
    }
    
    {
        std::cout << "Class C object on the heap.\n";
        C *pC = new C;
        delete pC; //one might imagine that in complicated programs it becomes somewhat burdensome to remember to do this
    }
    
    //Declaring shared pointers
    {
        //Integer is created on the heap and attaches sp1 to it. Recall we need to explicitly call the constructor for an integer (or any other object for that matter)
        std::shared_ptr<int> sp1(new int(5));
        
//        std::shared_ptr<int> s = new int(5);
        
        //Shared pointers keep track of how many owners an object has
        std::cout << sp1.use_count() << "\n";
        
        //Many smart pointers can own the same object, with each one we attach we see the count increase!
        std::shared_ptr<int> sp2 = sp1;
        std::cout << sp1.use_count() << "\n";
        
        {
            std::shared_ptr<int> sp3 = sp1;
            std::cout << sp1.use_count() << "\n";
        }
        //After the completion of this scope the count is now down to two as sp3, being a stack variable, has gone out of scope!
        std::cout << sp1.use_count() << "\n";
    }
    //After this scope has finished the count on the integer 5 on the heap drops to 0 and it will automatically be deleted, no memory leaks!
    
    //Dereferencing of shared pointers works the same as raw pointers
    {
        std::shared_ptr<C> sp1 (new C);
        std::cout << "\nMemory address of C object: " << sp1 << "\nvalue of C object: " << sp1->i << "\n";
    }
    
    std::cout << "\nMultiple scopes example:\n";
    {//Scope 1
        std::shared_ptr<C> sp1;
        
        {//Scope 2
            std::shared_ptr<C> sp2 (new C);
            sp1 = sp2;
            {
                std::shared_ptr<C> sp3 = sp1;
                std::cout << sp1.use_count() << "\n";
            }
            std::cout << "Exited scope 3\n";
            std::cout << sp1.use_count() << "\n";
        }
        std::cout << "Exited scope 2\n";
        std::cout << sp1.use_count() << "\n";
    }
    std::cout << "Exited scope 1\n"; // With the end of scope 1 all smart pointers to the C object are destroyed
    
    std::cout << "\nStudy 2: unique pointers\n";
    
    {
        std::unique_ptr<C> up1 (new C);
        //Unlike shared pointers we aren't allowed to attach other objects to this object, both of the following will result in errors! If we were implementing these smart pointers itself, there might be an = delete on copy/move constructors, as well as no implicit conversions
//        std::unique_ptr<C> up2 = up1;
//        std::shared_ptr<C> sp1 = up1;
    }
    std::cout << std::endl;
    {
        std::unique_ptr<C> up1 (new C);
        //Once bound we can't simply reassign a unique pointer, indeed the following will cause an error
//        up1 = new C;
        std::cout << up1.get() << "\n";
        //We can however reset the unique pointer, and point at a new type C object for instance
        up1.reset(new C); //Indeed doing this calls the destructor for the type C object!
        std::cout << up1.get() << "\n";
    }
    
    std::cout << "\nStudy 3: weak pointers\n";
    
    /*
     Motivation: overcoming circular dependencies between shared pointers! Let's think about a dog and human class
     */
    {
        std::cout << "Attempt 1: \n";
        std::shared_ptr<Human1> jeff(new Human1);
        std::shared_ptr<Dog1> lassie(new Dog1);
        jeff->dog = lassie;
        lassie->human = jeff;
        
        //Observe both objects now have a count of 2!
        std::cout << lassie.use_count()<< "\n";
        std::cout << jeff.use_count()<< "\n";
        
        //No destructors are called because each object sees there are two owners, so they delete themselves and decrease the ownership to one --> memory leak
        /*
         No destructors were called at exit! We have a memory leak here becuase of circular referncing of the share pointers. Remember, if a class of type object1 contains a shared pointer to a class of type object2 then it owns that object. Here we have created a Human1 and Dog1 object which both own one another... Recall construction and destructoon on the stack happen in reverse order, threfore, in particular lassie and jeff are not destroyed at the same time. The issue above is that when the lassie pointer is destoyed the associated Dog1 object on the heap is not deleted as the count associated with it is 1 not 0. When the jeff pointer is then destroyed likewise there is still a Dog1 object on the heap pointed at the Human1 object associated with Jeff, so the counter is likewise 1 not 0. As a result neither are deleted!
         */
    }
    
    //Weak pointers give us a workaround
    {
        std::cout << "Attempt 2: \n";
        std::shared_ptr<Human2> jeff(new Human2);
        std::shared_ptr<Dog2> lassie(new Dog2);
        jeff->dog = lassie;
        lassie->human = jeff;
        
        //Observe both objects now do not have a count of 2
        std::cout << lassie.use_count()<< "\n";
        std::cout << jeff.use_count()<< "\n";
    }
    
    
    return 0;
}
