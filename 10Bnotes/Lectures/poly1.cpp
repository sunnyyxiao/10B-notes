//
//  poly1.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 1/26/24.
//

#include <iostream>
#include <iomanip>
#include <vector>
#include "clocks.hpp"

/*
 Polymorphism means "many formed". In the context of programming, think of having a single interface which allows objects to exhibit their differences. We want a container which contains different objects and we want these objects to be able to exhibit their differences through the same overloaded function calls.
 A specific example: we want to have a 'list' of Clock and TravelClock objects, and want to be able to pass through these clocks and call the appropriate overridden or overloaded memmber function, in particular the << operator
 
 1) Attempt 1: vector of clock objects
 2) Attempt 2: vector of pointers to clock objects
 3) Attempt 3: same as before, but make relevant member functions of base class 'virtual'
 */

int main(){
    
    //What happens if we put TravelClocks in a vector of Clocks?
    {
        std:: cout << "Vector of Clocks: \n";
        
        Clock c1(true);
        TravelClock c2(true, "LA", -8);
        TravelClock c3(false, "Berlin", 1);
        
        std::vector<Clock> clocks = {c1,c2,c3};
        
        for (size_t i = 0; i < 3; i++){
            std::cout << clocks[i] << "\n";
        }
        
        //Travel clocks have been converted to clocks!
        
    }
    
    //Pointers
    {
        std::cout << "\nPointing Clock pointers at TravelClocks and vice versa: \n";
        Clock c1(true);
        TravelClock c2(true, "LA", -7);
        Clock* p1 = &c2;
        TravelClock* p2 = &c2;
        std::cout << p1 << " " << p2 << "\n";
        
        //these are the same, the initial lump of memory used to store a TravelClock is the same as the lump of memory storing the base Clock (pointers have same hexadecimal number)
        
        //Changing member variables to public --> then run this line, you will see objects of class are stored one after the other!
//        std::cout << &(p1->am_pm) << " " << &(p2-> location) << " " << &(p2->td) << "\n";
        
        //The following instruction causes an error, note we will discuss rvalues in the next section! However, if you try to store a Clock object in a TravelClock pointer, this will build and run because the Clock class is the base class.
//        p2 = &c1;
        
        //What if we try to access member functions and variables of a TravelClock object through a clock pointer? If you try to call extend_example then it won't work...p1 is a Clock pointer and and clocks don't have a time_diff member, even if the object is pointing at does!
        
        p2->extend_example();
//      p1->extend_example(); //Does not work :(
        
        std::cout << p1->am_pm;
//        std::cout << p1->location; //Does not work either!
        
    }
    
    {
        
        //What happens when we use a vector of Clock pointers to point at both Clocks and TravelClocks? As long as we use the keyword virtual then we are okay!
        {
            std::cout << "\n\nVector of Clock pointers:\n";
            std::vector<Clock*> clocks;
            Clock c1(true);
            TravelClock c2(true, "LA", -8);
            TravelClock c3(false, "Berlin", 1);
            Clock* cp1 = &c1;
            clocks.push_back(cp1);
            Clock* cp2 = &c2;
            clocks.push_back(cp2);
            Clock* cp3 = &c3;
            clocks.push_back(cp3);
            
            std::cout << cp1->get_hours() << std::endl;
            
            for (size_t i = 0; i < 3; i++){
                /*
                 If we don't use virtual, they will be Clock member functions and operators, not TravelClock ones!
                 */
                std::cout << *clocks[i] << "\n";
            }
        }
        /*
         Why does this work? If we use virtual on the member functions called inside the operator overload for the Clock class then the actual function used (the clock or Travel clock) is decided at runtime rather than at compilation (static)
         
         Observe: at compile time, the compiler knows only that the argument will, of an operator in this case, be a reference to an object derived a Clock; it cannot determine whether the argument will be a reference to an object of type Clock or type TravelClock. However, this can be determined at runtime.
         
         The virtual keyword indicates to the compiler that it should choose the appropriate definition of the member operator in this example not by the type of reference, but by the type of object that the reference refers to. It happens at runtime.
         
         The virtual keyword can only be used in the base class, and all overridden functions are thus virtual as well. Only member functions (not global functions or variables) can be virtual.
         */
    }
    return 0;
}
