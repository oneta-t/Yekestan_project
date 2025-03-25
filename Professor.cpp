#include "Professor.h"
#include "Cours.h"

Professor::Professor(string uname, string pwd, string name, string family, int id) : User(uname, pwd)
{
    Firstname = name;
    Lastname = family;
    next_P = nullptr;
    teachingCourse = nullptr;
}

string Professor::get_firstname()
{
    return Firstname;
}

string Professor::get_lastname()
{
    return Lastname;
}

int Student::get_id()
{
    return Id;
}

Professor *Professor::get_nextP()
{
    return next_P;
}

void Professor::set_nextP(Professor *nextP)
{
    next_P = nextP;
}

void Professor::Sign_in(Professor *&headProfessor)
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
            cout << MAGENTA << "✨ Login was successful ✨" << RESET << endl;
            // اینجا باید ببینیم که آیا فرد دانشجو هست یا استاد که بتونه وارد بخش کاربری خودش بره
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
    cout << MAGENTA << "✨ Registration was successful ✨" << RESET << endl;
}

void Professor::Add_professor(Professor *&headProfessor, Professor *newprofessor)
{
    newprofessor->set_nextP(headProfessor);
    headProfessor = newprofessor;
}

void Professor::create_cours(string name, string college, int units, int capacity, float score, float average, string day, string time) // اینجا خروجی رو بعدا اگه به مشکل خورد تغییر میدم
{
    Cours *newcours = new Cours(name, college, units, capacity, score, average, day, time, this);
    newcours->set_next_cours(teachingCourse);
    teachingCourse = newcours;
}

void Professor::display_students(Cours *cours)
{
    if (cours->get_Professor() != this)
    {
        cerr << RED << "This cours does not belong to you" << RESET << endl;
        return;
    }
    Student *students = cours->get_Students();
    cout << "\033[1;32m" << "List of students:" << RESET << endl;
    while (students != nullptr)
    {
        cout << GREEN << students->get_firstname() << " " << students->get_lastname() << "\t" << "Student ID: " << students->get_id() << RESET << endl;
        students = students->get_nextS();
    }
}

void Professor::create_task(Cours *cours, string nametaske, string description, string deadline)
{
    if (cours->get_Professor() != this)
    {
        cerr << RED << "This cours does not belong to you" << RESET << endl;
        return;
    }
    Task *newtasks = new Task(nametaske, description, deadline);
    cours->Addtask(newtasks);
}

void Professor::score_task(Cours *cours, int id, float score)
{
    Task *current = cours->get_Tasks();
    cout << "\033[1;32m" << "List of tasks:" << RESET << endl;
    while (current != nullptr)
    {
        cout << GREEN << current->get_nametask() << "\t" << current->get_deadline() << endl
             << current->get_description() << RESET << endl;
        current = current->get_next_task();
        cout << YELLOW << "*_______*       *_______*       *_______*       *_______*       *_______*" << RESET << endl;
    }
    cout << "Pleas enter name of task you want to grad:" << endl;
    string nametask;
    cin >> nametask;
    current = cours->get_Tasks();
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
            cout << BLUE << temp->get_student_name() << "\t" << "Studeny ID:" << temp->get_id() << endl
                 << "Answer: " << temp->get_answer() << RESET << endl;
            float grade;
            cout << "Pleas enter scour: " << endl;
            cin >> grade;
            temp->set_score(grade);
            cout << MAGENTA << "Grading completed successfully" << RESET << endl;
        }
        current = current->get_next_task();
    }
    cerr << RED << "Invalid task selection" << RESET << endl;
}
