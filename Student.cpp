#include "Student.h"
#include "Cours.h"

Student::Student(string uname, string pwd, string name, string family, string major, int id) : User(uname, pwd)
{
    Firstname = name;
    Lastname = family;
    Major = major;
    Id=id;
}

string Student::get_firstname()
{
    return Firstname;
}

string Student::get_lastname()
{
    return Lastname;
}

string Student::get_major()
{
    return Major;
}

int Student::get_id()
{
    return Id;
}

Student *Student::get_nextS()
{
    return next_S;
}

void Student::set_nextS(Student *nextS)
{
    next_S = nextS;
}

void Student::Sign_in_S(Student *&headStudent)
{
    string username, password;
    cout << YELLOW << "Pleas enter your username:" << RESET << endl;
    cin >> username;
    cout << YELLOW << "Pleas enter your password:" << RESET << endl;
    cin >> password;

    Student *temp = headStudent;
    while (temp != nullptr)
    {
        if (temp->get_username() == username && temp->get_password() == password)
        {
            cout << MAGENTA << "✨ Login was successful ✨" << RESET << endl;
            // اینجا باید ببینیم که آیا فرد دانشجو هست یا استاد که بتونه وارد بخش کاربری خودش بره
            return;
        }
        temp = temp->get_nextS();
    }
    cerr << RED << "Username or password is incorrect" << RESET << endl;
    return;
}

void Student::Sign_up_S(Student *&headStudent)
{
    string username, password1, password2, firstname, lastname, major;
    int id;
    cout << YELLOW << "Pleas enter your firstname:" << RESET << endl;
    cin >> firstname;
    cout << YELLOW << "Pleas enter your lastname:" << RESET << endl;
    cin >> lastname;
    cout << YELLOW << "Pleas enter your major:" << RESET << endl;
    cin >> major;
    cout << YELLOW << "Pleas enter your username:" << RESET << endl;
    cin >> username;
    Student*temp=headStudent;
    while (temp!=nullptr)
    {
        while (temp->get_username()==username)
        {
            cerr<<RED<<"This username already exists. Please enter a new username:"<<RESET<<endl;
            cin >> username;
        }
        temp=temp->get_nextS();
    }    
    cout << YELLOW << "Pleas enter your password:" << RESET << endl;
    cin >> password1;
    cout << YELLOW << "Please repeat your password again:" << RESET << endl;
    cin >> password2;
    while (password1!=password2)
    {
        cerr<<RED<<"The entered password does not match. Please try again and enter passsword:"<<RESET<<endl;
        cin >> password2;
    }
    cout << YELLOW << "Pleas enter your student Id:" << RESET << endl;
    cin >> id;

    Student *newstudent = new Student(username, password1, firstname, lastname, major, id);
    Add_student(headStudent, newstudent);
    cout << MAGENTA << "✨ Registration was successful ✨" << RESET << endl;
}

void Student::Add_student(Student *&headStudent, Student *newstudent)
{
    newstudent->set_nextS(headStudent);
    headStudent = newstudent;
}
