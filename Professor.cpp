#include "Professor.h"

Professor::Professor(string uname, string pwd, string name, string family, int id) : User(uname, pwd)
{
    Firstname = name;
    Lastname = family;
    Id = id;
    next_P = nullptr;
    teachingCourse = nullptr;
    isActiveP = true;
}

Professor::~Professor()
{
    Cours *tempCours = teachingCourse;
    while (tempCours != nullptr)
    {
        Cours *nextCours = tempCours->get_next_cours();
        delete tempCours;
        tempCours = nextCours;
    }
}

string Professor::get_firstname()
{
    return Firstname;
}

string Professor::get_lastname()
{
    return Lastname;
}

int Professor::get_id()
{
    return Id;
}

bool Professor::get_isActiveP()
{
    return isActiveP;
}

void Professor::set_isActiveP(bool x)
{
    isActiveP = x;
}

Professor *Professor::get_nextP()
{
    return next_P;
}

void Professor::set_nextP(Professor *nextP)
{
    next_P = nextP;
}

void Professor::Sign_in_P(Professor *&headProfessor, Cours *&courses, Student *&all_student)
{
    string username, password;
    cout << YELLOW << "Pleas enter your username:" << RESET << endl;
    cin >> username;
    cout << YELLOW << "Pleas enter your password:" << RESET << endl;
    cin >> password;

    Professor *temp = headProfessor;
    while (temp != nullptr)
    {
        if (temp->get_username() == username && temp->get_password() == password)
        {
            cout << endl;
            cout << MAGENTA << "*** Login was successful ***" << RESET << endl;
            this->professor_page(courses, all_student, headProfessor);
            return;
        }
        temp = temp->get_nextP();
    }
    cerr << RED << "Username or password is incorrect" << RESET << endl;
    return;
}

void Professor::Sign_up_P(Professor *&headProfessor)
{
    string username, password1, password2, firstname, lastname;
    int id;
    cout << YELLOW << "Pleas enter your firstname:" << RESET << endl;
    cin >> firstname;
    cout << YELLOW << "Pleas enter your lastname:" << RESET << endl;
    cin >> lastname;
    cout << YELLOW << "Pleas enter your username:" << RESET << endl;
    cin >> username;
    Professor *temp = headProfessor;
    while (temp != nullptr)
    {
        while (temp->get_username() == username)
        {
            cerr << RED << "This username already exists. Please enter a new username:" << RESET << endl;
            cin >> username;
        }
        temp = temp->get_nextP();
    }
    cout << YELLOW << "Pleas enter your password:" << RESET << endl;
    cin >> password1;
    cout << YELLOW << "Please repeat your password again:" << RESET << endl;
    cin >> password2;
    while (password1 != password2)
    {
        cerr << RED << "The entered password does not match. Please try again and enter passsword:" << RESET << endl;
        cin >> password2;
    }
    cout << YELLOW << "Pleas enter your Id:" << RESET << endl;
    cin >> id;
    Professor *newprofessor = new Professor(username, password1, firstname, lastname, id);
    Add_professor(headProfessor, newprofessor);
    save_professors(headProfessor);
    cout << MAGENTA << "*** Registration was successful ***" << RESET << endl;
}

void Professor::Add_professor(Professor *&headProfessor, Professor *newprofessor)
{
    newprofessor->set_nextP(headProfessor);
    headProfessor = newprofessor;
}

void Professor::create_cours(Cours *&headCourses, Professor *&headProfessor, Student *&allS, string name, string profname, string profamily, string college, int units, int capacity, string day, string time) // اینجا خروجی رو بعدا اگه به مشکل خورد تغییر میدم
{
    Cours *newcours1 = new Cours(allS, name, college, profname, profamily, units, capacity, day, time);
    newcours1->set_next_cours(teachingCourse);
    teachingCourse = newcours1;

    Cours *newcours2 = new Cours(allS, name, college, profname, profamily, units, capacity, day, time);
    newcours2->set_next_cours(headCourses);
    headCourses = newcours2;
    save_professors(headProfessor);
    save_courses(headCourses);
}

void Professor::display_students(Cours *cours, Student *allStd)
{
    if (cours->get_Professorname() != Firstname || cours->get_Professorfamaly() != Lastname)
    {
        cerr << RED << "This cours does not belong to you" << RESET << endl;
        return;
    }
    vector<int> StdID = cours->get_stdID();
    if (StdID.empty())
    {
        cout << RED << "No students enrolled in this course yet." << RESET << endl;
        return;
    }
    Student *temp = allStd;
    if (temp == nullptr)
    {
        cerr << RED << "The list of students is empty." << RESET << endl;
        return;
    }
    cout << "\033[1;32m" << "List of students:" << RESET << endl;
    while (temp != nullptr)
    {
        for (size_t i = 0; i < StdID.size(); i++)
        {
            if (temp->get_id() == StdID[i])
            {
                cout << GREEN << temp->get_firstname() << " " << temp->get_lastname() << "\t" << "Student ID: " << temp->get_id() << RESET << endl;
            }
        }
        temp = temp->get_nextS();
    }
}

void Professor::create_task(Cours *&headcours, Cours *cours, string nametaske, string description, string deadline)
{
    if (cours->get_Professorname() != Firstname || cours->get_Professorfamaly() != Lastname)
    {
        cerr << RED << "This cours does not belong to you" << RESET << endl;
        return;
    }
    Task *newtasks = new Task(nametaske, description, deadline);
    cours->Addtask(newtasks);
    save_courses(headcours);
}

void Professor::score_task(Student *&all_student)
{
    Cours *cours = teachingCourse;
    Student *students = all_student;
    if (cours == nullptr)
    {
        cerr << RED << "You are not offering any courses this semester" << RESET << endl;
        return;
    }
    cout << "\033[1;32m" << "List of courses you teach :" << RESET << endl;
    while (cours != nullptr)
    {
        cout << GREEN << "ID: " << cours->get_id() << ") " << cours->get_Coursename() << RESET << endl;
        cours = cours->get_next_cours();
    }
    cout << endl;
    cout << "Please enter the ID of the course you want: " << endl;
    int num;
    cin >> num;
    cours = teachingCourse;
    while (cours != nullptr)
    {
        if (cours->get_id() == num)
        {
            vector<int> StdID = cours->get_stdID();
            if (StdID.empty() || students == nullptr)
            {
                cout << RED << "No students enrolled in this course yet." << RESET << endl;
                return;
            }
            cout << "\033[1;32m" << "List of students :" << RESET << endl;
            while (students != nullptr)
            {
                for (size_t i = 0; i < StdID.size(); i++)
                {
                    if (students->get_id() == StdID[i])
                    {
                        cout << GREEN << students->get_firstname() << " " << students->get_lastname() << "\t" << "Student ID: " << students->get_id() << RESET << endl;
                    }
                }
                students->get_nextS();
            }
            cout << endl;
            cout << "Please enter the ID of the student you want to add score to submission: " << endl;
            int id;
            cin >> id;
            students = all_student;
            while (students != nullptr)
            {
                if (students->get_id() == id)
                {
                    Cours *STDcours = students->get_list_courses();
                    while (STDcours != nullptr)
                    {
                        if (STDcours->get_id() == cours->get_id())
                        {
                            Task *current = STDcours->get_Tasks();
                            if (current == nullptr)
                            {
                                cerr << RED << "No tasks available for this course." << RESET << endl;
                                return;
                            }
                            int count = 0;
                            cout << "\033[1;32m" << "List of tasks:" << RESET << endl;
                            while (current != nullptr)
                            {
                                ++count;
                                cout << "Task" << count << ") " << current->get_nametask() << endl;
                                current = current->get_next_task();
                            }
                            cout << endl;
                            cout << "Pleas enter name of task you want to grad:" << endl;
                            string nametask;
                            cin >> nametask;
                            current = STDcours->get_Tasks();
                            while (current != nullptr)
                            {
                                if (current->get_nametask() == nametask)
                                {
                                    Submission *temp = current->get_Submissions();
                                    if (temp == nullptr)
                                    {
                                        cout << RED << "No submissions found for this task" << RESET << endl;
                                        return;
                                    }
                                    cout << "Answer: " << temp->get_answer() << RESET << endl;
                                    float grade;
                                    cout << "Pleas enter scour: " << endl;
                                    cin >> grade;
                                    temp->set_score(grade);
                                    save_students(all_student);
                                    cout << MAGENTA << "*** Grading completed successfully ***" << RESET << endl;
                                }
                                current = current->get_next_task();
                            }
                        }
                        STDcours = STDcours->get_next_cours();
                    }
                    return;
                }
                students = students->get_nextS();
            }
            return;
        }
        cours = cours->get_next_cours();
    }
}

void Professor::score_student(Student *&all_student)
{
    Cours *cours = teachingCourse;
    Student *students = all_student;
    if (cours == nullptr)
    {
        cerr << RED << "You are not offering any courses this semester" << RESET << endl;
        return;
    }
    cout << "\033[1;32m" << "List of courses you teach :" << RESET << endl;
    while (cours != nullptr)
    {
        cout << GREEN << "ID:" << cours->get_id() << " " << cours->get_Coursename() << RESET << endl;
        cours = cours->get_next_cours();
    }
    cout << endl;
    cout << "Please enter the ID of the course you want: " << endl;
    int num;
    cin >> num;
    cours = teachingCourse;
    while (cours != nullptr)
    {
        if (cours->get_id() == num)
        {
            vector<int> StdID = cours->get_stdID();
            if (StdID.empty() || students == nullptr)
            {
                cout << RED << "No students enrolled in this course yet." << RESET << endl;
                return;
            }
            cout << "\033[1;32m" << "List of students :" << RESET << endl;
            while (students != nullptr)
            {
                for (size_t i = 0; i < StdID.size(); i++)
                {
                    if (students->get_id() == StdID[i])
                    {
                        cout << GREEN << students->get_firstname() << " " << students->get_lastname() << "\t" << "Student ID: " << students->get_id() << RESET << endl;
                    }
                }
                students = students->get_nextS();
            }
            cout << endl;
            cout << "Please enter the ID of the student you want to add score: " << endl;
            int id;
            cin >> id;
            students = all_student;
            while (students != nullptr)
            {
                if (students->get_id() == id)
                {
                    float grade;
                    cout << "Please enter scour:" << endl;
                    cin >> grade;
                    Cours *list_courses = students->get_list_courses();
                    while (list_courses != nullptr)
                    {
                        if (list_courses == cours)
                        {
                            list_courses->set_score(grade);
                            save_students(all_student);
                            cout << MAGENTA << "*** Grading completed successfully ***" << RESET << endl;
                            return;
                        }
                        list_courses = list_courses->get_next_cours();
                    }
                }
                students = students->get_nextS();
            }
        }
        cours = cours->get_next_cours();
    }
}

void Professor::Add_notification(Professor *&headprof, Cours *&headcours)
{
    Cours *cours = teachingCourse;
    if (cours == nullptr)
    {
        cerr << RED << "You are not offering any courses this semester" << RESET << endl;
        return;
    }
    cout << "\033[1;32m" << "List of courses you teach :" << RESET << endl;
    while (cours != nullptr)
    {
        cout << GREEN << cours->get_Coursename() << RESET << endl;
        cours = cours->get_next_cours();
    }
    cout << endl;
    cout << "Please enter the Id of the course you want add notice: " << endl;
    int id;
    cin >> id;
    cours = teachingCourse;
    while (cours != nullptr)
    {
        if (cours->get_id() == id)
        {
            string notice;
            cout << "Please enter the text of the notice:" << endl;
            getline(cin, notice);
            cours->add_Notice(notice);
            save_courses(headcours);
            save_professors(headprof);
            cout << MAGENTA << "*** Announcement added successfully ***" << RESET << endl;
            return;
        }
        cours = cours->get_next_cours();
    }
}

Cours *Professor::get_teachingCourse()
{
    return teachingCourse;
}

void Professor::set_teachingCourse(Cours *courses)
{
    teachingCourse = courses;
}

void Professor::professor_page(Cours *&courses, Student *&all_student, Professor *&headProfessor)
{
    Student *students = all_student;
    Professor *prof = headProfessor;
    cout << MAGENTA << "*** Welcome to your page ***" << RESET << endl;
    while (1)
    {
        cout << GREEN << "Please select one of the items." << endl;
        cout << "1)Create a new course\n2)Showing the students of a course\n3)Create a new task for course\n4)Grading tasks\n5)Grading students\n6)Add notification\n7)View the course you teach\n0)end" << RESET << endl;
        cout << "Please enter the desired number: " << endl;
        int num;
        cin >> num;
        switch (num)
        {
        case 0:
            return;
        case 1:
        {
            cout << "Please enter your ID: " << endl;
            int ID;
            string name, profname, profamily, college, day, time;
            cin.ignore();
            cin >> ID;
            while (prof != nullptr)
            {
                if (ID == prof->get_id())
                {
                    profname = prof->Firstname;
                    profamily = prof->Lastname;
                    break;
                }
                prof=prof->get_nextP();
            }
            cin.ignore();
            cout << "Please enter the name of course: " << endl;
            getline(cin, name);
            cout << "Please enter the relevant College: " << endl;
            getline(cin, college);
            cout << "Please enter the class day(For example:Saturday-Monday): " << endl;
            getline(cin, day);
            cout << "Please enter the class time(For example:15:00-17:00): " << endl;
            getline(cin, time);
            int units, capacity;
            cout << "Please enter the number of course units: " << endl;
            cin >> units;
            cout << "Please specify the course capacity: " << endl;
            cin >> capacity;
            prof->create_cours(courses, headProfessor, students, name, profname, profamily, college, units, capacity, day, time);
            break;
        }
        case 2:
        {
            cout << "Please enter the course ID for which you want to see the students: " << endl;
            int num1;
            cin >> num1;
            Cours *current = courses;
            if (current == nullptr)
            {
                cerr << RED << "There are no courses offered this semester." << RESET << endl;
                return;
            }
            while (current != nullptr)
            {
                if (current->get_id() == num1)
                {
                    this->display_students(current, students);
                    break;
                }
                current = current->get_next_cours();
            }
            cerr << RED << "There is no courrse with that ID." << RESET << endl;
        }
        break;
        case 3:
        {
            cout << "Please enter the course ID for which you want to see the students: " << endl;
            int num2;
            cin >> num2;
            Cours *current = courses;
            if (current == nullptr)
            {
                cerr << RED << "There are no courses offered this semester." << RESET << endl;
                return;
            }
            while (current != nullptr)
            {
                if (current->get_id() == num2)
                {
                    cout << "Please enter the task name: " << endl;
                    string nametaske, description, deadline;
                    getline(cin, nametaske);
                    cout << "Please enter the description: " << endl;
                    getline(cin, description);
                    cout << "Please specify the deadline: " << endl;
                    getline(cin, deadline);
                    this->create_task(courses, current, nametaske, description, deadline);
                    break;
                }
                current = current->get_next_cours();
            }
            cerr << RED << "There is no courrse with that ID." << RESET << endl;
        }
        break;
        case 4:
            this->score_task(students);
            break;
        case 5:
            this->score_student(students);
            break;
        case 6:
            this->Add_notification(headProfessor, courses);
            break;
        case 7:
            this->view_courses();
            break;
        default:
            break;
        }
    }
}

void Professor::view_courses()
{
    Cours *courses = teachingCourse;
    if (courses == nullptr)
    {
        cerr << RED << "You have not taken any courses this semester." << RESET << endl;
        return;
    }
    cout << "\033[1;32m" << "List of courses you have taken this semester :" << RESET << endl;
    while (courses != nullptr)
    {
        cout << GREEN << "Id: " << courses->get_id() << "      Name: " << courses->get_Coursename() << "       College: " << courses->get_College() << RESET << endl;
        cout << endl;
        courses = courses->get_next_cours();
    }
    cout << endl;
}