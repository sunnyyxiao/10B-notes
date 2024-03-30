//
//  clocks.hpp
//  PIC10B
//
//  Created by Sunny Xiao on 1/24/24.
//

#ifndef clocks_hpp
#define clocks_hpp

#include <string>

class Clock{
public:
    Clock(bool _am_pm);
    virtual int get_hours() const;
    int get_minutes() const;
    virtual std::string get_location() const;
    friend std::ostream& operator << (std::ostream& os, const Clock& right);
    //Explore what happens when we make am_pm private or protected
//protected:
    bool am_pm;
//    virtual std::ostream& information(std::ostream& os) const;
};


/*
 Member variables
 - inherit am_pm, and extend location and time_diff
 - make new members protected
 
 Member functions and operators
 - extend constructor: takes in clock type, location, time difference
 - inherit get_minutes
 - override get_hours as have to adjust for time difference
 - override get_location as not necessarily UTC!
 - override output stream operator
 - etxend some function just for demonstration purposes
 */

// Note if public is not included here your code will still compile, however your derived class will not have access to the public member functions and member variables of the base class.
class TravelClock: public Clock{
public:
    //Constructor
    TravelClock(bool _am_pm, std::string _location, int _td);
    //Overrides
    virtual int get_hours() const override;
    virtual std::string get_location() const override;
    void extend_example() const;
    friend std::ostream& operator << (std::ostream& os, const TravelClock& right);
    
protected:
    std::string location;
    int td; //time difference
//    virtual std::ostream& information(std::ostream& os) const override;
};

class CoolClock: public TravelClock{
protected:
    std::string color;
    void alarm_sound() const;
};

#endif /* clocks_hpp */

