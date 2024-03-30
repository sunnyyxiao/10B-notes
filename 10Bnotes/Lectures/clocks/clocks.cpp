//
//  clocks.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 1/24/24.
//

#include "clocks.hpp"
#include <iomanip>
#include <iostream>

Clock::Clock(bool _am_pm):am_pm(_am_pm) {}

int Clock::get_hours() const{
    return (int(std::time(nullptr))%(86400))/3600;
}

int Clock::get_minutes() const{
    return ((int(std::time(nullptr))%(86400))%3600)/60;
}

std::string Clock::get_location() const{
    return "UTC";
}

std::ostream& operator << (std::ostream& os, const Clock& right){
//    return right.information(os);
    os << "(" << right.get_location() << ")";
    int hrs = right.get_hours();
    if (right.am_pm){
        if (hrs>12){
            hrs%=12;
            os << hrs << ":" << right.get_minutes() << "pm";
        }
        else{
            os << hrs << ":" << right.get_minutes() << "am";
        }
    }
    else{
        os << hrs << ":" << right.get_minutes();
    }
    return os;
}

/*
 Constructor of derived class
 - takes in clock type, location (string) and time difference
 - should construct the base object in the initializer list, call the constructor for the base class before the constructor of the derived class
 */

TravelClock::TravelClock(bool _am_pm, std::string _location, int _td): Clock::Clock(_am_pm), location(_location),td(_td)/*,extra("extra var")*/{}
/*
 Override get hours
 - need the hours and location functions to take into account the time difference and location information (no longer UTC!)
 - call the base class get hours
 - then need to ensure wrap around 0-24 hours
 */
int TravelClock::get_hours() const {
    int hours = Clock::get_hours() + td; //need to tell compiler to use base class or else this function becomes recursive
    if (hours < 0){
        hours += 24;
    } else if (hours >= 24){
        hours -= 24;
    }
    return hours;
}

/*
 Override get_location
 - needs to return the location member variable rather than the string UTC
 */
std::string TravelClock::get_location() const {
    return location;
}

/*
 Extending example
 - example function which isn't in the base class
 */
void TravelClock::extend_example() const {
    std::cout << "Hey this is a new member function which is only for TravelClocks, not Clocks" << std::endl;
}

/*
 Overload << operator
 - note is not a member function, we therefore cannot use virtual
 If we do not overload this operator, the << operator will use the Clock one (only can use the base class functions/members --> location is always UTC and time is always UTC)
 */
std::ostream& operator << (std::ostream& os, const TravelClock& right) {
    os << "(" << right.get_location() << ")";
    int hrs = right.get_hours();
    // If am_pm is private member of Clock, we can't access from TravelClock --> need to use a getter. However, since this is protected, we can directly access it
    if (right.am_pm){
        if (hrs>12){
            hrs%=12;
            os << hrs << ":" << right.get_minutes() << "pm travel clock print ";
        }
        else{
            os << hrs << ":" << right.get_minutes() << "am travel clock print";
        }
    }
    else{
        os << hrs << ":" << right.get_minutes() << " travel clock print";
    }
    return os;
}

//std::ostream& Clock::information(std::ostream& os) const{
//    os << "hello " << get_location() << ")";
//    int hrs = get_hours();
//    if (am_pm){
//        if (hrs>12){
//            hrs%=12;
//            os << hrs << ":" << get_minutes() << "pm";
//        }
//        else{
//            os << hrs << ":" << get_minutes();
//        }
//    }
//    else{
//        os << hrs << ":" << get_minutes();
//    }
//    return os;
//}

//std::ostream& TravelClock::information(std::ostream& os) const{
//    os << "Travel clock print" << get_location() << ")";
//    int hrs = get_hours();
//    if (am_pm){
//        if (hrs>12){
//            hrs%=12;
//            os << hrs << ":" << get_minutes() << "pm";
//        }
//        else{
//            os << hrs << ":" << get_minutes();
//        }
//    }
//    else{
//        os << hrs << ":" << get_minutes();
//    }
//    return os;
//}
