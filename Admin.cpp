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
        cout << "Professor: " << courses->get_Professorname() << " " << courses->get_Professorfamaly() << "        Time: " << courses->get_day() << "-->" << courses->get_time() <<endl;
        courses->Calculate_average();
        cout<<"Average score of students: "<<courses->get_average_Scores()<<RESET<<endl;//اینجا یه چیزی برا این میخوام که مثلادانشجو نمره بده و میانگینو نشون بده
        cout << YELLOW << "*_______*       *_______*       *_______*       *_______*       *_______*" << RESET << endl;
        courses=courses->get_next_cours();
    }
}


void create_student(Student*& headStudent)
{
    
}