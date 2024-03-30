//
//  employees2.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 1/31/24.
//

#include "employees2.hpp"

/*
 Abstract class Employee member function definitions:
 - default constructor
 - constructor taking in two integers
 */

Employee::Employee(int _salary, int _contracted_hours): hourly_salary(_salary), contracted_hours(_contracted_hours){}

Employee::Employee():hourly_salary(30),contracted_hours(40){}

/*
 Class Worker member function definitions:
 - wage function definition from last time
 */

int Worker::wage(int hours_worked) const {
    int overtime_hours = 0;
    if (hours_worked>contracted_hours){
        overtime_hours += hours_worked-contracted_hours;
    }
    return hourly_salary*(hours_worked + overtime_hours*2);
}


/*
 Class Contracter member function definitions
 - wage function definition from last time
 */
int Contracter::wage(int hours_worked) const {
    return hourly_salary*hours_worked;
}
