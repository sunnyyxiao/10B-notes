//
//  operators2.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 1/19/24.
//

#include <iostream>
#include <iomanip>

/*
 Agenda:
 We will write a Time class which wil store time in terms of the format HH:MM:SS
 1) Overloading input and output streams
 2) Overloading the subscript operator
 3) Overloading conversion operators
 4) Ambiguous and implicit conversions + the explicit keyword
 
 In particular we will implement
 - output stream operator overload '<<'
 - input stream operator overload '>>'
 - subscript operator overload '[]'
 - '-' operator overload
 - int type convertion operator overload
 */

//Time class definition
class Time{
private:
    int hours;
    int minutes;
    int seconds;
public:
    //Constructors: note we have a way of mapping an int to a Time object
    Time(int _hours, int _minutes, int _seconds):hours(_hours), minutes(_minutes), seconds(_seconds){}
    /*explicit */Time(int _hours):hours(_hours), minutes(0), seconds(0){}
    Time():hours(0), minutes(0), seconds(0){}
    
    //Friend global functions implementing ostream and istream overloads. Declare << as a friend inside class as we need to access private members of right. Note not implemented as member functions as left argument of '<<' operator is an input or output stream (cin or cout). Although we could implement both the input and output stream operator overloads as streams we can also use the copy constructor to avoid this at least for the input stream operator.
    
    //A stream is a sequence of characters we're going to send somewhere
    //Friend function cannot be void because cout << object << endl turns into void << endl
    friend std::ostream& operator << (std::ostream& out, const Time& right);
    
    //Subscript operator []: lets define the subscript operator so that [0] corresponds to the hours, [1] the minutes and anything else to seconds. Also return a reference so we can change these values! The subscript operator overload is best implement as a class member operator, this way the implicit parameter is a class object, i.e. the object outside the brackets, and the explicit parameter is the subscript or key
    
    //Reference allows us to change the values of the private member variables with the operator
    int& operator [] (int i){
        if (i == 0){
            int& r = hours;
            return r;
        } else if (i == 1){
            int& r = minutes;
            return r;
        } else {
            int& r = seconds;
            return r;
        }
    }

    
    //Let us allow declare a friend function for subtracting two times
    friend Time operator - (const Time& left, const Time& right);
    
    
    //Note that we now have a way of mapping from Time to integers, but also a constructor which maps from integers to Time objects. We will see this introduces an ambiguity when it comes to subtracting a time from an integer or visa versa.
//    operator int (){
//        return 3600*hours + 60*minutes + seconds;
//    }
};

//Definition of << overload, note needs to be a friend! Also can use std::setw(2) << std::setfill('0') to buffer single digit numbers with an extra 0 digit, i.e. print 01 rather than 1
std::ostream& operator << (std::ostream& out, const Time& right){
    out << std::setw(2) << std::setfill('0') << right.hours << ":" << std::setw(2) << std::setfill('0') << right.minutes << ":" << std::setw(2) << std::setfill('0') << right.seconds;
    return out;
}

//Definition of >> overload, note does not necessarily need to be a friend if we use copy constructor (more on copy constructor later)
std::istream& operator >> (std::istream& in, Time& right){
    int h, m, s;
    in >> h >> m >> s; //console waits for user to input integers
    right = Time(h,m,s); //copy constructor to copy this over to right
    return in;
}

Time operator - (const Time& left, const Time& right){
    return Time((left.hours-right.hours)%24, (left.minutes-right.minutes)%60, (left.seconds-right.seconds)%60);
}

/*
 Summary
 - implement as global functions
 - should mutate input/output stream, so always pass stream by reference
 - should also return a reference to std::istream or std::ostream to enable chaining
 - two arguments
 */

/*
 Conversions
 
 
 */

int main(){
    Time t(1,2,3);
    
    std::cout << "The time is " << t << ", that is quite early!" << std::endl;
    
    Time start;
    std::cin >> start;
    std::cout << "The start time is " << start << " in military time format\n";
    
    std::cout << "Hours of start is equal to " << start[0] << "\n";
    ++start[0];
    std::cout << "After incrementing by 1 hour start is now " << start << "\n";
    
    Time finish(10,11,12);
//    Time difference = finish - start;
//    std::cout << "The difference in time between finish and start is " << difference << std::endl;
    
    //40 hours = finish - 40 hours
    //Ambiguity when you have the int operator that can convert Time objects to integers = the compiler doesn't know if it should convert the Time object to an integer and do integer subtraction, then convert the resulting integer using the constructor, or convert the integer to a Time object using the constructor and use the - operator
    //Using the explicit keyword before a constructor means you can't use the constructor implicitly, but in this case, you must use the constructor implicitly in both cases to get what you want
    Time other = finish - 40;
    std::cout << other << std::endl;
    return 0;
}
