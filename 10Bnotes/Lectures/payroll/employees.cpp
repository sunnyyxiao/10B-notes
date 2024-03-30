//
//  employees.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 1/29/24.
//

#include "employees.hpp"

// Worker member definitions
Worker::Worker(int _contracted_hours, int _hourly_salary):contracted_hours(_contracted_hours), hourly_salary(_hourly_salary){}
Worker::Worker():contracted_hours(40), hourly_salary(30){}
int Worker::wage(int hours_worked) const{
    int overtime_hours = 0;
    if (hours_worked>contracted_hours){
        overtime_hours += hours_worked-contracted_hours;
    }
    return hourly_salary*(hours_worked + overtime_hours*2);
}

// Contracter member definitions
Contracter::Contracter(int _hourly_salary):Worker::Worker(0, _hourly_salary){}
Contracter::Contracter():Worker::Worker(0, 30){}

int Contracter::wage (int hours_worked) const{
    return hourly_salary*hours_worked;
}


// Payroll member definitions

Payroll::Payroll(): hours(),workers(){}

int Payroll::total_wages(){
    size_t size = workers.size();
    int total = 0;
    for (int i = 0; i < size; i++){
        total += workers[i]->wage(hours[i]);
    }
    return total;
}
