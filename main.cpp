#include "Student.h"
#include "Professor.h"
#include "Admin.h"

int main()
{

    cout << MAGENTA << "✨ Welcome to the Yekestan program ✨" << RESET << endl;
    cout << endl;
    cout << GREEN << "Please select one of the items" << endl;
    cout << "1) I'm admin\n2)I have already registered\n3)I want to register now" << RESET << endl;
    int num;
    cin>>num;
    switch (num)
    {
    case 1:
        //بره بخش ادمین و پیده سازی اون
        break;
    case 2:
        //بخش اینه اصلا استاده یا دانشجو و بعد وارد بخش کاربری
        break;
    case 3:
        //دوباره بپرسه که دانشجو هست یا ن وو ادامه بده به زندگانیش
        break;
    default:
    
        break;
    }

    return 0;
}