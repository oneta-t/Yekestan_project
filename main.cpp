#include "Student.h"
#include "Cours.h"
#include "Professor.h"
#include "Admin.h"
#include "save_load.h"

void cleanUp(Student *&headStudent, Professor *&headProfessor, Cours *&headCourses)
{
    Student *tempStudent = headStudent;
    while (tempStudent != nullptr)
    {
        Student *nextStudent = tempStudent->get_nextS();
        delete tempStudent;
        tempStudent = nextStudent;
    }
    headStudent = nullptr;
    Professor *tempProfessor = headProfessor;
    while (tempProfessor != nullptr)
    {
        Professor *nextProfessor = tempProfessor->get_nextP();
        delete tempProfessor;
        tempProfessor = nextProfessor;
    }
    headProfessor = nullptr;
    Cours *tempCourse = headCourses;
    while (tempCourse != nullptr)
    {
        Cours *nextCourse = tempCourse->get_next_cours();
        delete tempCourse;
        tempCourse = nextCourse;
    }
    headCourses = nullptr;
}

int main()
{
    Student *students = load_students();
    Professor *professors = load_professors(students);
    Cours *courses = load_courses(students);

    if (courses != nullptr && students != nullptr && professors != nullptr)
    {
        cerr << RED << "Error: Failed to load data!" << RESET << endl;
        return 0;
    }
    cout << endl;
    cout << MAGENTA << "✨ Welcome to the Yekestan program ✨" << RESET << endl;
    cout << endl;
    while (1)
    {
        cout << GREEN << "Please select one of the items.For example, if you are a student and want to register, enter number 35 or if you are a professor and have already registered, enter number 24, if you are also an admin, enter only the number 1 and end with the number 0" << endl;
        cout << "1)I'm Admin\n2)I'm Professor\n3)I'm Student\n4)I have already registered\n5)I want to register now" << RESET << endl;
        cout << "Please enter the desired number: " << endl;
        int num;
        cin >> num;
        Student *student = nullptr;
        Professor *prof = nullptr;
        switch (num)
        {
        case 1:
        {
            string username, password;
            cout << YELLOW << "Pleas enter your username:" << RESET << endl;
            cin >> username;
            cout << YELLOW << "Pleas enter your password:" << RESET << endl;
            cin >> password;
            if (username != "admin" || password != "123456") // کسی که میخواهید وارد بخش ادمین شود باید رمز را 123456و نام کاربری را adminوارد کند
            {
                cerr << RED << "Username or password is incorrect." << RESET << endl;
                break;
            }
            Admin_page(courses, students, professors);
        }
        break;
        case 24:
            prof->Sign_in_P(professors, courses, students);
            break;
        case 25:
            prof->Sign_up_P(professors);
            break;
        case 34:
            student->Sign_in_S(students, courses);
            break;
        case 35:
            student->Sign_up_S(students);
            break;
        default:
            cerr << RED << "The number entered is incorrectPlease try again." << RESET << endl;
            break;
        case 0:
            return 0;
        }
    }
    save_students(students);
    save_professors(professors);
    save_courses(courses);
    cleanUp(students, professors, courses);

    return 0;
}