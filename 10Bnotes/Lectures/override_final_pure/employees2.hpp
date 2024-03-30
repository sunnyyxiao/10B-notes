//
//  employees2.hpp
//  PIC10B
//
//  Created by Sunny Xiao on 1/31/24.
//

#ifndef employees2_hpp
#define employees2_hpp

/*
 Employee delcaration
 - constructor + default constructor
 - virtual wage function (should be pure!)
 - hourly salary and contracted hours
 
 Worker declaration, inherits from Employee
 - inherit the constructors of Employee via 'using'
 - override the wage function (you have to as is pure in base class!) and make sure you override
 - inherit member variables
 
 Contracter declaration, inherits from Employee
 - inherit the constructors of Employee via 'using'
 - override the wage function (you have to as is pure in base class!) and make sure you override
 - inherit member variables
 */

class Employee{
public:
    Employee();
    Employee(int _salary, int _contracted_hours);
    virtual int wage(int hours_worked) const = 0;
protected:
    int hourly_salary;
    int contracted_hours;
};

class Worker : public Employee{
public:
    //using inherits all constructors from base class (all or nothing)
    using Employee::Employee;
    virtual int wage(int hours_worked) const override;
};

class Contracter : public Employee{
public:
    using Employee::Employee;
    virtual int wage(int hours_worked) const override;
    
};

#endif /* employees2_hpp */
