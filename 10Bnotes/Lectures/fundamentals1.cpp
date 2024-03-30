//
//  fundamentals1.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 1/8/24.
//

/*
 Review concepts:
 - Building an executable (preprocessing, compiling, linking
 - Hello world, terminal input and output, basic arithmetic
 - Variables
 - Scope
 - Control flow
 */

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main(){
    //Hello world and cout, role of the terminal
    cout << "Hello world\n";
    
    //Some basic arithmetic
    cout << 5+3*2 << " " << 10%2 << endl;
    
    /*
     Introduce some global variables (int, double, string) and declaration, assignment
     - Declaration, initialization, assignment
     - Variable types + const
     - Examples, assigning variables to each other
     */
    
    int x = 2;
    char c = 'a';
    string s = "Hello world";
    double d = 1.5;
    
    x*=10;
    int y = 4;
    x = y;
    x = c;
    cout << x << endl;
    
    //Scope and scope test
    {
        int i = 1, j = 2, k = 3;
        {
            int j = 20, k = 30;
            {
                int k = 300;
                cout << i << " " << j << " " << k << endl;
            }
            cout << i << " " << j << " " << k << endl;
        }
        cout << i << " " << j << " " << k << endl;
    }
    
    //Cin
//    {
//        int x;
//        cin >> x;
//        cout << 2*x << endl;
//
//    }
    {
        int x, y, z;
        cin >> x >> y >> z;
        cout << z << " " << y << " " << x << endl;
        
        double d;
        string s;
        cin >> d;
        getline(cin,s);
        cout << d << endl;
        cout << s;
    }
    
    //CONTROL FLOW EXERCISES
    //If statement example: identify if user inputted integer is positive, zero, or negative
    {
        double d;
        cin >> d;
        if (d > 0){
            if (d > 0){
                if (d > 0){
                    if (d == 0){
                        cout << "Your integer is zero." << endl;
                    }
                    else cout << "Your integer is positive." << endl;
                } else cout << " Your integer is negative." << endl;
            }
        }        
    }
    return 0;
}
