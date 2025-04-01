#include "Student.h"
#include "Cours.h"
#include "Professor.h"
#include "Admin.h"

int main()
{
    Cours*headcourse=nullptr;
    Student*headstd=nullptr;
    Professor*headprof=nullptr;

    cout << MAGENTA << "✨ Welcome to the Yekestan program ✨" << RESET << endl;
    cout << endl;
    while (1)
    {
        cout << GREEN << "Please select one of the items.For example, if you are a student and want to register, enter number 35 or if you are a professor and have already registered, enter number 24, if you are also an admin, enter only the number 1 and end with the number 0" << endl;
        cout << "1)I'm Admin\n2)I'm Professor\n3)I'm Student\n4)I have already registered\n5)I want to register now" << RESET << endl;
        int num;
        cin >> num;
        switch (num)
        {
        case 1:
            Admin_page(headcourse,headstd,headprof);
            break;
        case 24:
            // بخش اینه اصلا استاده یا دانشجو و بعد وارد بخش کاربری
            break;
        case 25:
            // دوباره بپرسه که دانشجو هست یا ن وو ادامه بده به زندگانیش
            break;
        case 34:
            // دوباره بپرسه که دانشجو هست یا ن وو ادامه بده به زندگانیش
            break;
        case 35:
            // دوباره بپرسه که دانشجو هست یا ن وو ادامه بده به زندگانیش
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