//
//  employees.hpp
//  PIC10B
//
//  Created by Sunny Xiao on 1/29/24.
//

#ifndef employees_hpp
#define employees_hpp

#include <iostream>
#include <string>
#include <cmath>
#include <vector>

// Worker class declaration has been done for you
class Worker{
public:
    Worker(int _contracted_hours, int _hourly_salary);
    Worker();
    virtual int wage(int hours_worked) const;
protected:
    int hourly_salary;
    int contracted_hours;
};

// The Contracter class declaration needs to be done by you!
class Contracter : public Worker{
public:
    Contracter(int _hourly_salary);
    Contracter();
    virtual int wage(int hours_worked) const;
};

// Payroll declaration has been done for you
class Payroll{
public:
    Payroll();
    std::vector <int> hours;
    std::vector <Worker*> workers;
    int total_wages();
};



#endif /* employees_hpp */
