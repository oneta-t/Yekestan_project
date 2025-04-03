#include "Student.h"
#include "Cours.h"
#include "Professor.h"
#include "Admin.h"

int main()
{
    Cours *headcourse = nullptr;
    Student *headstd = nullptr;
    Professor *headprof = nullptr;

    cout << MAGENTA << "✨ Welcome to the Yekestan program ✨" << RESET << endl;
    cout << endl;
    while (1)
    {
        cout << GREEN << "Please select one of the items.For example, if you are a student and want to register, enter number 35 or if you are a professor and have already registered, enter number 24, if you are also an admin, enter only the number 1 and end with the number 0" << endl;
        cout << "1)I'm Admin\n2)I'm Professor\n3)I'm Student\n4)I have already registered\n5)I want to register now" << RESET << endl;
        cout << "Please enter the desired number: " << endl;
        int num;
        cin >> num;
        Student *student;
        Professor *prof;
        switch (num)
        {
        case 1:
        {
            string username, password;
            cout << YELLOW << "Pleas enter your username:" << RESET << endl;
            cin >> username;
            cout << YELLOW << "Pleas enter your password:" << RESET << endl;
            cin >> password;
            if (username!="admin" || password!="123456")//کسی که میخواهید وارد بخش ادمین شود باید رمز را 123456و نام کاربری را adminوارد کند
            {
                cerr<<RED<<"Username or password is incorrect."<<RESET<<endl;
                break;
            }          
            Admin_page(headcourse, headstd, headprof);
        }
        break;
        case 24:
            prof->Sign_in_P(headprof, headcourse);
            break;
        case 25:
            prof->Sign_up_P(headprof);
            break;
        case 34:
            student->Sign_in_S(headstd, headcourse);
            break;
        case 35:
            student->Sign_up_S(headstd);
            break;
        default:
            cerr << RED << "The number entered is incorrectPlease try again." << RESET << endl;
            break;
        case 0:
            return;
        }
    }
    return 0;
}