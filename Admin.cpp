#include "Admin.h"

void Admin::view_all_students(Student *headStudent)
{
    Student *STD = headStudent;
    if (STD == nullptr)
    {
        cerr << RED << "The student list is empty." << RESET << endl;
        return;
    }
    cout << "\033[1;32m" << "List of student this semester :" << RESET << endl;
    cout << endl;
    while (STD != nullptr)
    {
        if (STD->get_isActiveS() == true)
        {
            cout << GREEN << STD->get_firstname() << " " << STD->get_lastname() << "         Student ID: " << STD->get_id() << "        Major: " << STD->get_major() << RESET << endl;
            cout << endl;
        }
        STD = STD->get_nextS();
    }
}

void Admin::view_all_professors(Professor *headProfessor)
{
    Professor *prof = headProfessor;
    if (prof == nullptr)
    {
        cerr << RED << "The professor list is empty." << RESET << endl;
        return;
    }
    cout << "\033[1;32m" << "List of professor this semester :" << RESET << endl;
    cout << endl;
    while (prof != nullptr)
    {
        if (prof->get_isActiveP() == true)
        {
            cout << GREEN << prof->get_firstname() << " " << prof->get_lastname() << "         professor ID: " << prof->get_id() << RESET << endl;
            cout << endl;
        }
        prof = prof->get_nextP();
    }
}

void Admin::view_all_courses(Cours *headCourse)
{
    Cours *courses = headCourse;
    if (courses == nullptr)
    {
        cerr << RED << "The courses list is empty." << RESET << endl;
        return;
    }
    cout << "\033[1;32m" << "List of courses this semester :" << RESET << endl;
    cout << endl;
    while (courses != nullptr)
    {
        cout << GREEN << "Cours name: " << courses->get_Coursename() << "       Units: " << courses->get_units() << "        College: " << courses->get_College() << endl;
        cout << "Professor: " << courses->get_Professorname() << " " << courses->get_Professorfamaly() << "        Time: " << courses->get_day() << "-->" << courses->get_time() << endl;
        courses->Calculate_average();
        cout << "Average score of students: " << courses->get_average_Scores() << RESET << endl; // اینجا یه چیزی برا این میخوام که مثلادانشجو نمره بده و میانگینو نشون بده
        cout << YELLOW << "*_______*       *_______*       *_______*       *_______*       *_______*" << RESET << endl;
        courses = courses->get_next_cours();
    }
}

void Admin::create_student(Student *&headStudent)
{
    cout << "Please enter the firstname: " << endl;
    string name;
    cin >> name;
    cout << "Please enter the lastname: " << endl;
    string family;
    cin >> family;
    cout << "Please enter the major: " << endl;
    string major;
    cin >> major;
    cout << "Please enter the student ID: " << endl;
    int Id;
    cin >> Id;
    cout << "Please enter the username: " << endl;
    string username;
    cin >> username;
    Student *current = headStudent;
    while (current != nullptr)
    {
        while (username == current->get_username())
        {
            cerr << RED << "This username already exists. Please enter a new username:" << RESET << endl;
            cin >> username;
        }
        current = current->get_nextS();
    }
    cout << "Please enter the password: " << endl;
    string pass;
    cin >> pass;
    Student *newStudent = new Student(username, pass, name, family, major, Id);
    newStudent->set_nextS(headStudent);
    headStudent = newStudent;
    cout << MAGENTA << "✨ Registration was successful ✨" << RESET << endl;
}

void Admin::create_professor(Professor *&headProfessor)
{
    cout << "Please enter the firstname: " << endl;
    string name;
    cin >> name;
    cout << "Please enter the lastname: " << endl;
    string family;
    cin >> family;
    cout << "Please enter the professor ID: " << endl;
    int Id;
    cin >> Id;
    cout << "Please enter the username: " << endl;
    string username;
    cin >> username;
    Professor *prof = headProfessor;
    while (prof != nullptr)
    {
        while (username == prof->get_username())
        {
            cerr << RED << "This username already exists. Please enter a new username:" << RESET << endl;
            cin >> username;
        }
        prof = prof->get_nextP();
    }
    cout << "Please enter the password: " << endl;
    string pass;
    cin >> pass;
    Professor *newprof = new Professor(username, pass, name, family, Id);
    newprof->set_nextP(headProfessor);
    headProfessor = newprof;
    cout << MAGENTA << "✨ Registration was successful ✨" << RESET << endl;
}

void Admin::delete_student(Student *headStudent)
{
    cout << "Please enter the student ID of the student you want to delete: " << endl;
    int id;
    cin >> id;
    Student *current = headStudent;
    if (current == nullptr)
    {
        cerr << RED << "The student list is empty." << RESET << endl;
        return;
    }
    while (current != nullptr)
    {
        if (id == current->get_id())
        {
            current->set_isActiveS(false);
            cout << MAGENTA << "✨ Student successfully deleted ✨" << RESET << endl;
            return;
        }
        current = current->get_nextS();
    }
    cerr << RED << "There is no student with this ID in the student list." << RESET << endl;
}

void Admin::delete_professor(Professor *headProfessor)
{
    cout << "Please enter the student ID of the professor you want to delete: " << endl;
    int id;
    cin >> id;
    Professor *current = headProfessor;
    if (current == nullptr)
    {
        cerr << RED << "The professor list is empty." << RESET << endl;
        return;
    }
    while (current != nullptr)
    {
        if (id == current->get_id())
        {
            current->set_isActiveP(false);
            cout << MAGENTA << "✨ professor successfully deleted ✨" << RESET << endl;
            return;
        }
        current = current->get_nextP();
    }
    cerr << RED << "There is no professor with this ID in the professor list." << RESET << endl;
}

void Admin::restore_student(Student *headStudent)
{
    cout << "Please enter the student ID of the student you want to restore: " << endl;
    int id;
    cin >> id;
    Student *current = headStudent;
    if (current == nullptr)
    {
        cerr << RED << "The student list is empty." << RESET << endl;
        return;
    }
    while (current != nullptr)
    {
        if (id == current->get_id())
        {
            current->set_isActiveS(true);
            cout << MAGENTA << "✨ Student successfully restore ✨" << RESET << endl;
            return;
        }
        current = current->get_nextS();
    }
    cerr << RED << "There is no student with this ID in the student list." << RESET << endl;
}

void Admin::restore_professor(Professor *headProfessor)
{
    cout << "Please enter the student ID of the professor you want to restore: " << endl;
    int id;
    cin >> id;
    Professor *current = headProfessor;
    if (current == nullptr)
    {
        cerr << RED << "The professor list is empty." << RESET << endl;
        return;
    }
    while (current != nullptr)
    {
        if (id == current->get_id())
        {
            current->set_isActiveP(false);
            cout << MAGENTA << "✨ professor successfully restore ✨" << RESET << endl;
            return;
        }
        current = current->get_nextP();
    }
    cerr << RED << "There is no professor with this ID in the professor list." << RESET << endl;
}

void Admin_page(Cours *headcourse, Student *headstd, Professor *headprof)
{
    cout << MAGENTA << "✨ Welcome to the admin page ✨" << RESET << endl;
    cout << endl;
    while (1)
    {
        cout << GREEN << "Please select one of the items." << endl;
        cout << "1)view students\t2)view professors\t3)view courses\n4)create student\t5)create professor\n6)delete student\t7)delete professor\n8)restore student\t9)restore professsor\t0)end" << RESET << endl;
        cout << "Please enter the desired number: " << endl;
        int num;
        cin >> num;
        Admin* admin;
        switch (num)
        {
        case 0:
            return;
        case 1:
            admin->view_all_students(headstd);
            break;
        case 2:
            admin->view_all_professors(headprof);
            break;
        case 3:
            admin->view_all_courses(headcourse);
            break;
        case 4:
            admin->create_student(headstd);
            break;
        case 5:
            admin->create_professor(headprof);
            break;
        case 6:
            admin->delete_student(headstd);
            break;
        case 7:
            admin->delete_professor(headprof);
            break;
        case 8:
            admin->restore_student(headstd);
            break;
        case 9:
            admin->restore_professor(headprof);
            break;
        default:
        cerr << RED << "The number entered is incorrect. Please try again." << RESET << endl;
        break;
        }
    }
}