#include "Student.h"
#include "Cours.h"

Student::Student(string uname, string pwd, string name, string family, string major, int id) : User(uname, pwd)
{
    Firstname = name;
    Lastname = family;
    Major = major;
    Id = id;
    list_courses = nullptr;
    next_S = nullptr;
    isActiveS = true;
}

Student::~Student()
{
    Cours *tempCours = list_courses;
    while (tempCours != nullptr)
    {
        Cours *nextCours = tempCours->get_next_cours();
        delete tempCours;
        tempCours = nextCours;
    }
    next_S = nullptr;
    list_courses = nullptr;
}

const string Student::get_firstname()const 
{
    return Firstname;
}

const string Student::get_lastname()const
{
    return Lastname;
}

const string Student::get_major()const
{
    return Major;
}

int Student::get_id()const
{
    return Id;
}

bool Student::get_isActiveS()const
{
    return isActiveS;
}

void Student::set_isActiveS(bool x)
{
    isActiveS = x;
}

Cours *Student::get_list_courses()
{
    return list_courses;
}
void Student::set_list_courses(Cours *courses)
{
    list_courses = courses;
}

Student *Student::get_nextS()
{
    return next_S;
}

void Student::set_nextS(Student *nextS)
{
    next_S = nextS;
}

void Student::student_page(Cours *&courses, Student *&headStudent)
{
    cout << MAGENTA << "*** Welcome to your page ***" << RESET << endl;
    while (1)
    {
        cout << GREEN << "Please select one of the items." << endl;
        cout << "1)View registered courses this semester\n2)View available courses this semester\n3)Register for the desired course\n4)View task scores\n5)Answerthe tasks\n6)Grad to course\n7)view notice of course\n0)end" << RESET << endl;
        cout << "Please enter the desired number: " << endl;
        int num;
        cin >> num;
        switch (num)
        {
        case 0:
            return;
        case 1:
            this->View_registered_courses();
            break;
        case 2:
            this->view_Available_Courses(courses);
            break;
        case 3:
            this->Course_registration(courses, headStudent);
            break;
        case 4:
            this->view_Task_Grades();
            break;
        case 5:
            this->Answer_to_task(headStudent);
            break;
        case 6:
            this->Grading_course(headStudent);
            break;
        // case 7:
        //     this->Grading_course(headStudent);//اینجا باید اطلاعیه درس رو بتونی ببینی
        //     break;
        default:
            cerr << RED << "The number entered is incorrect. Please try again." << RESET << endl;
            break;
        }
    }
}

void Student::Sign_in_S(Student *&headStudent, Cours *&courses)
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
            cout << endl;
            cout << MAGENTA << "*** Login was successful ***" << RESET << endl;
            this->student_page(courses, headStudent);
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
    Student *temp = headStudent;
    while (temp != nullptr)
    {
        while (temp->get_username() == username)
        {
            cerr << RED << "This username already exists. Please enter a new username:" << RESET << endl;
            cin >> username;
        }
        temp = temp->get_nextS();
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
    cout << YELLOW << "Pleas enter your student Id:" << RESET << endl;
    cin >> id;

    Student *newstudent = new Student(username, password1, firstname, lastname, major, id);
    Add_student(headStudent, newstudent);
    save_students(headStudent);
    cout << MAGENTA << "*** Registration was successful ***" << RESET << endl;
}

void Student::Add_student(Student *&headStudent, Student *newstudent)
{
    newstudent->set_nextS(headStudent);
    headStudent = newstudent;
}

void Student::View_registered_courses()
{
    Cours *courses = list_courses;
    if (courses == nullptr)
    {
        cerr << RED << "You have not taken any courses this semester." << RESET << endl;
        return;
    }
    cout << "\033[1;32m" << "List of courses you have taken this semester :" << RESET << endl;
    while (courses != nullptr)
    {
        cout << CYAN << "Id: " << courses->get_id() << "      Name: " << courses->get_Coursename() << "       College: " << courses->get_College() << "       Time: " << courses->get_day() << "-->" << courses->get_time();
        cout << endl;
        cout << "       Professor: " << courses->get_Professorname() << " " << courses->get_Professorfamaly() << "        Average_Scores: " << courses->get_average_Scores() << "        Score: " << courses->get_score();
        cout << endl;
        courses = courses->get_next_cours();
        cout << YELLOW << "*_______*       *_______*       *_______*       *_______*       *_______*" << RESET << endl;
    }
    cout << endl;
}

void Student::view_Available_Courses(Cours *allcourses)
{
    string currentCollege = "";
    Cours *current = allcourses;
    if (current == nullptr)
    {
        cerr << RED << "There are no courses offered this semester." << RESET << endl;
        return;
    }
    cout << endl;
    cout << "\033[1;32m" << "List of courses offered this semester :" << RESET << endl;
    cout << endl;
    while (current != nullptr)
    {
        bool collegeExists = false;
        Cours *check = allcourses;
        while (check != nullptr)
        {
            if (check->get_College() == current->get_College())
            {
                collegeExists = true;
                break;
            }
            check = check->get_next_cours();
        }
        if (collegeExists == true)
        {
            cout << GREEN << "     ==== College " << current->get_College() << " ====     " << RESET << endl;
            cout << endl;
            Cours *courses = allcourses;
            while (courses != nullptr)
            {
                if (courses->get_College() == current->get_College())
                {
                    cout << CYAN << "Id: " << courses->get_id() << "      Name: " << courses->get_Coursename() << "       Professor: " << courses->get_Professorname() << " " << courses->get_Professorfamaly() << "       Time: " << courses->get_day() << "-->" << courses->get_time() << "\n";
                    cout << "Units: " << courses->get_units() << "         Number of people registered: ( " << courses->get_registeredS() << "/" << courses->get_capacity() << " )" << RESET << endl;
                    cout << YELLOW << "*_______*       *_______*       *_______*       *_______*       *_______*" << RESET << endl;
                    cout << endl;
                }
                courses = courses->get_next_cours();
            }
        }
        current = current->get_next_cours();
    }
}

void Student::Course_registration(Cours *&allcourses, Student *&headStudent)
{
    cout << "Please enter the course ID you want to add to your course list: " << endl;
    int num;
    cin >> num;
    Cours *courses = allcourses;
    Cours *targetCourse = nullptr;
    if (courses == nullptr)
    {
        cerr << RED << "There are no courses offered this semester." << RESET << endl;
        return;
    }
    while (courses != nullptr)
    {
        if (courses->get_id() == num)
        {
            targetCourse = courses;
            break;
        }
        courses = courses->get_next_cours();
    }
    if (targetCourse == nullptr)
    {
        cerr << RED << "Course with ID " << num << " not found!" << RESET << endl;
        return;
    }
    if (targetCourse->get_registeredS() >= targetCourse->get_capacity())
    {
        cerr << RED << "The course is full.You cannot add this course to your course list." << RESET << endl;
        return;
    }
    Cours *registeredC = list_courses;
    while (registeredC != nullptr)
    {
        if (registeredC->get_id() == targetCourse->get_id())
        {
            cerr << RED << "You are already registered for this course!" << RESET << endl;
            return;
        }
        registeredC = registeredC->get_next_cours();
    }
    Cours *newCourse = new Cours(*targetCourse);
    newCourse->set_next_cours(list_courses);
    list_courses = newCourse;
    // targetCourse->Addstudent(this->get_id());
    // targetCourse->set_next_cours(list_courses);
    // list_courses = targetCourse;
    save_students(headStudent);
    save_courses(allcourses);
    cout << MAGENTA << "*** Registration was successful ***" << RESET << endl;
}

void Student::view_Task_Grades()
{
    cout << "Please enter the course ID you want to see task score: " << endl;
    int num;
    cin >> num;
    Cours *courses = list_courses;
    if (courses == nullptr)
    {
        cerr << RED << "You have not taken any courses this semester." << RESET << endl;
        return;
    }
    while (courses != nullptr)
    {
        if (courses->get_id() == num)
        {
            Task *tasks = courses->get_Tasks();
            if (tasks == nullptr)
            {
                cerr << RED << "There are no tasks for this course." << RESET << endl;
                return;
            }
            int count = 0;
            while (tasks != nullptr)
            {
                Submission *sub = tasks->get_Submissions();
                if (sub == nullptr)
                {
                    cerr << RED << "There are no submissions for this task." << RESET << endl;
                    return;
                }
                ++count;
                cout << GREEN << "Task" << count << " --> " << tasks->get_nametask() << "         Score: " << sub->get_score() << RESET << endl;
                cout << endl;
                tasks = tasks->get_next_task();
            }
            return;
        }
        courses = courses->get_next_cours();
    }
}

void Student::Answer_to_task(Student *&headStudent)
{
    cout << "Please enter the course ID you want to add submission: " << endl;
    int num;
    cin >> num;
    Cours *courses = list_courses;
    if (courses == nullptr)
    {
        cerr << RED << "You have not taken any courses this semester." << RESET << endl;
        return;
    }
    while (courses != nullptr)
    {
        if (courses->get_id() == num)
        {
            Task *tasks = courses->get_Tasks();
            if (tasks == nullptr)
            {
                cerr << RED << "There are no tasks for this course." << RESET << endl;
                return;
            }
            int count = 0;
            cout << "\033[1;32m" << "List of tasks:" << RESET << endl;
            while (tasks != nullptr)
            {
                ++count;
                cout << GREEN << "Task" << count << " --> " << tasks->get_nametask() << RESET << endl;
                cout << endl;
                tasks->get_next_task();
            }
            cout << "Please enter the name of taske you want: " << endl;
            string name;
            cin >> name;
            tasks = courses->get_Tasks();
            while (tasks != nullptr)
            {
                if (name == tasks->get_nametask())
                {
                    cout << GREEN << "Deadline: " << tasks->get_deadline() << "          Description: " << tasks->get_description() << RESET << endl;
                    cout << "Please enter your answer for this task:" << endl;
                    string answer;
                    getline(cin, answer);
                    tasks->Add_Submissions(this->Firstname, this->Id, answer);
                    save_students(headStudent);
                    cout << MAGENTA << "*** Your answer was successfully added ***" << RESET << endl;
                    return;
                }
                tasks = tasks->get_next_task();
            }
            cerr << RED << "There is no task with that name." << RESET << endl;
            return;
        }
        courses = courses->get_next_cours();
    }
    cerr << RED << "There is no courrse with that ID." << RESET << endl;
    return;
}

void Student::Grading_course(Student *&headStudent)
{
    cout << "Please enter the course ID you want to add grad for course: " << endl;
    int num;
    cin >> num;
    Cours *courses = list_courses;
    if (courses == nullptr)
    {
        cerr << RED << "You have not taken any courses this semester." << RESET << endl;
        return;
    }
    while (courses != nullptr)
    {
        if (courses->get_id() == num)
        {
            cout << "Please enter the grad you want to add to this course(The score range is from 0 to 20): " << endl;
            float grad;
            cin >> grad;
            while (grad > 20 || grad < 0)
            {
                cerr << RED << "The score you entered is not in the range of 0-20. Please try again:" << RESET << endl;
                cin >> grad;
            }
            courses->add_Student_rating(Id, grad);
            save_students(headStudent);
            cout << MAGENTA << "*** Your grad was successfully added to this course ***" << RESET << endl;
            return;
        }
        courses = courses->get_next_cours();
    }
    cerr << RED << "No course with such ID was found." << RESET << endl;
}

void Student::view_notice()
{
    cout << "Please enter the course ID you want to see notice : " << endl;
    int num;
    cin >> num;
    Cours *courses = list_courses;
    if (courses == nullptr)
    {
        cerr << RED << "You have not taken any courses this semester." << RESET << endl;
        return;
    }
    while (courses != nullptr)
    {
        if (courses->get_id() == num)
        {
            vector<string> allnotice = courses->get_Notice();
            cout << "\033[1:34m" << "Course announcements: " << RESET << endl;
            for (size_t i = 0; i < allnotice.size(); ++i)
            {
                cout << BLUE << i + 1 << ")" << allnotice[i] << endl;
                cout << endl;
                cout << "-------------------" << RESET << endl;
            }
        }
        courses = courses->get_next_cours();
    }
    cerr << RED << "No course with such ID was found." << RESET << endl;
}