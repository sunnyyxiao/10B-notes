//
//  inheritance1.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 1/24/24.
//

#include <iostream>
#include <iomanip>
#include "clocks.hpp"

/*
 Agenda
 - Base class case study: a Clock class
 - public vs protected vs private specifier on class members
 - Building a class on top of another class: inheritance
 - public vs protected vs private inheritance
 - Derived class case study: a time clock which is aware of its location
 */

int main(){
    //Demonstration of how to compute time
    //Note that we could do this much easier using the inbuilt library time.h!
    //To a basic degree we will try to re-implement some of its functionality
    {
        // Seconds since UTC 00:00:00 01/01/1970
        int s = int(std::time(nullptr));
        // Seconds since midnight today
        int sm = s%(24*60*60);
        // hours since midnight today
        int hrs = sm/(3600);
        // minutes since last hour
        int mins = (sm%3600)/60;
        std::cout<< "Current UTC time is " << hrs << ":" << mins << "\n" ;
        // Note LA is as of writing this 8 hours behind UTC
    }
    
    //Demonstration of Clock class
    {
        Clock c1(true);
        Clock c2(false);
        std::cout << c1 << "\n" << c2 << "\n";
    }
    
    //Demonstration of TravelClock class
    {
        TravelClock c1(true, "LA", -8);
        TravelClock c2(true, "Berlin", 1);
        std::cout << c1 << "\n" << c2 << "\n";
    }
    
}

