#include "Admin.h"

void Admin::view_all_students(Student *headStudent)
{
    Student *STD = headStudent;
    if (STD == nullptr)
    {
        cerr << RED << "The student list is empty." << RESET << endl;
        return;
    }
    cout << "\033[1;34m" << "List of student this semester :" << RESET << endl;
    cout << endl;
    while (STD != nullptr)
    {
        if (STD->get_isActiveS() == true)
        {
            cout << BLUE << STD->get_firstname() << " " << STD->get_lastname() << "         Student ID: " << STD->get_id() << "        Major: " << STD->get_major() << RESET << endl;
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
    cout << "\033[1;34m" << "List of professor this semester :" << RESET << endl;
    cout << endl;
    while (prof != nullptr)
    {
        if (prof->get_isActiveP() == true)
        {
            cout << BLUE << prof->get_firstname() << " " << prof->get_lastname() << "         professor ID: " << prof->get_id() << RESET << endl;
            cout << endl;
        }
        prof = prof->get_nextP();
    }
}

void Admin::view_all_courses(Cours *headCourse, Student *allSTD)
{
    Cours *courses = headCourse;
    if (courses == nullptr)
    {
        cerr << RED << "The courses list is empty." << RESET << endl;
        return;
    }
    cout << "\033[1;34m" << "List of courses this semester :" << RESET << endl;
    cout << endl;
    while (courses != nullptr)
    {
        cout << BLUE << "Cours name: " << courses->get_Coursename() << "       Units: " << courses->get_units() << "        College: " << courses->get_College() << endl;
        cout << "Professor: " << courses->get_Professorname() << " " << courses->get_Professorfamaly() << "        Time: " << courses->get_day() << "-->" << courses->get_time() << endl;
        courses->Calculate_average(allSTD);
        cout << "Average score of students: " << courses->get_average_Scores() << RESET << endl;
        cout << YELLOW << "*_______*       *_______*       *_______*       *_______*       *_______*" << RESET << endl;
        while (1)
        {
            cout << "If you want to see the grade that students have given for this course, enter the number 1, otherwise enter the number 0" << endl;
            int num;
            cin >> num;
            switch (num)
            {
            case 1:
            {
                cout << endl;
                cout << MAGENTA << "Student Ratings for " << courses->get_Coursename() << ":" << RESET << endl;
                const map<int, float> &ratings = courses->getAllRatings();
                if (ratings.empty())
                {
                    cout << YELLOW << "No student ratings available for this course." << RESET << endl;
                    return;
                }
                for (const auto &[studentId, rating] : ratings)
                {
                    Student *student = find_student_by_id(allSTD, studentId);
                    if (student != nullptr)
                    {
                        cout << student->get_firstname() << " " << student->get_lastname() << "\t\t" << studentId << "\t\t" << rating << "/20.0" << endl;
                    }
                }
                float sum = 0.0f;
                for (const auto &[_, rating] : ratings)
                {
                    sum += rating;
                }
                float average = sum / static_cast<float>(ratings.size());
                cout << "Average Rating: " << average << "/20.0" << endl;
            }
            break;
            case 0:
                return;
            default:
                cerr << RED << "The number entered is incorrect. Please try again." << RESET << endl;
                break;
            }
        }
        courses = courses->get_next_cours();
    }
}

Student *Admin::find_student_by_id(Student *head, int id) const
{
    Student *current = head;
    while (current != nullptr)
    {
        if (current->get_id() == id)
        {
            return current;
        }
        current = current->get_nextS();
    }
    return nullptr;
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
    save_students(headStudent);
    cout << MAGENTA << "*** Registration was successful ***" << RESET << endl;
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
    save_professors(headProfessor);
    cout << MAGENTA << "*** Registration was successful ***" << RESET << endl;
}

void Admin::delete_student(Student *&headStudent)
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
            save_students(headStudent);
            cout << MAGENTA << "*** Student successfully deleted ***" << RESET << endl;
            return;
        }
        current = current->get_nextS();
    }
    cerr << RED << "There is no student with this ID in the student list." << RESET << endl;
}

void Admin::delete_professor(Professor *&headProfessor)
{
    cout << "Please enter the professor ID of the professor you want to delete: " << endl;
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
            save_professors(headProfessor);
            cout << MAGENTA << "*** professor successfully deleted ***" << RESET << endl;
            return;
        }
        current = current->get_nextP();
    }
    cerr << RED << "There is no professor with this ID in the professor list." << RESET << endl;
}

void Admin::restore_student(Student *&headStudent)
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
            save_students(headStudent);
            cout << MAGENTA << "*** Student successfully restore ***" << RESET << endl;
            return;
        }
        current = current->get_nextS();
    }
    cerr << RED << "There is no student with this ID in the student list." << RESET << endl;
}

void Admin::restore_professor(Professor *&headProfessor)
{
    cout << "Please enter the professor ID of the professor you want to restore: " << endl;
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
            current->set_isActiveP(true);
            save_professors(headProfessor);
            cout << MAGENTA << "*** professor successfully restore ***" << RESET << endl;
            return;
        }
        current = current->get_nextP();
    }
    cerr << RED << "There is no professor with this ID in the professor list." << RESET << endl;
}

void Admin_page(Cours *headcourse, Student *headstd, Professor *headprof)
{
    cout << MAGENTA << "*** Welcome to the admin page ***" << RESET << endl;
    cout << endl;
    while (1)
    {
        cout << GREEN << "Please select one of the items." << endl;
        cout << "1)view students\n2)view professors\n3)view courses\n4)create student\n5)create professor\n6)delete student\n7)delete professor\n8)restore student\n9)restore professsor\n0)end" << RESET << endl;
        cout << "Please enter the desired number: " << endl;
        int num;
        cin >> num;
        //Admin *admin = nullptr;
        Admin admin;
        switch (num)
        {
        case 0:
            return;
        case 1:
            admin.view_all_students(headstd);
            break;
        case 2:
            admin.view_all_professors(headprof);
            break;
        case 3:
            admin.view_all_courses(headcourse, headstd);
            break;
        case 4:
            admin.create_student(headstd);
            break;
        case 5:
            admin.create_professor(headprof);
            break;
        case 6:
            admin.delete_student(headstd);
            break;
        case 7:
            admin.delete_professor(headprof);
            break;
        case 8:
            admin.restore_student(headstd);
            break;
        case 9:
            admin.restore_professor(headprof);
            break;
        default:
            cerr << RED << "The number entered is incorrect. Please try again." << RESET << endl;
            break;
        }
    }
}