//
//  payroll.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 1/29/24.
//

#include "employees.hpp"

int main(){
    {
        Contracter w1(1);
        std::cout << w1.wage(11);
    }
    
    {
        Payroll instructor;
        Contracter w1(100);
        Contracter w2(200);
        Worker w3;
        
        Worker* wp3 = &w3;
        
        (instructor.workers).push_back(&w1);
        (instructor.workers).push_back(&w2);
        (instructor.workers).push_back(wp3);
        
        (instructor.hours).push_back(1);
        (instructor.hours).push_back(2);
        (instructor.hours).push_back(3);
        
        std::cout << instructor.total_wages();
        
    }
    return 0;
}
