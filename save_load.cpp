#include "save_load.h"

void save_students(Student *headStudent)
{
    ofstream outFile("students.csv");
    if (!outFile)
    {
        cerr << "Error opening file for writing." << endl;
        return;
    }
    Student *temp = headStudent;
    while (temp != nullptr)
    {
        outFile << temp->get_id() << "," << temp->get_firstname() << "," << temp->get_lastname() << ","
                << temp->get_major() << "," << temp->get_username() << "," << temp->get_password() << ","
                << temp->get_isActiveS() << ",";
        Cours *courses = temp->get_list_courses();
        while (courses != nullptr)
        {
            outFile << courses->get_id() << "," << courses->get_Coursename() << ","
                    << courses->get_Professorname() << " " << courses->get_Professorfamaly() << "," << courses->get_College() << ","
                    << courses->get_day() << "," << courses->get_time() << "," << courses->get_units() << ","
                    << courses->get_registeredS() << "," << courses->get_capacity() << ","
                    << courses->get_score() << "," << courses->get_average_Scores() << ";";
            courses = courses->get_next_cours();
        }
        outFile << endl;
        temp = temp->get_nextS();
    }
    outFile.close();
}

Student *load_students()
{
    ifstream inFile("students.csv");
    if (!inFile)
    {
        cerr << "Error opening file for reading." << endl;
        return nullptr;
    }
    Student *headStudent = nullptr;
    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string token;
        vector<string> studentData;
        while (getline(ss, token, ','))
        {
            studentData.push_back(token);
        }
        int id = stoi(studentData[0]);
        string firstname = studentData[1];
        string lastname = studentData[2];
        string major = studentData[3];
        string username = studentData[4];
        string password = studentData[5];
        bool isActive = studentData[6] == "1";
        Student *newStudent = new Student(username, password, firstname, lastname, major, id);
        newStudent->set_isActiveS(isActive);
        stringstream coursesStream(studentData[7]);
        string courseToken;
        Cours *headCourse = nullptr;
        while (getline(coursesStream, courseToken, ';'))
        {
            stringstream courseData(courseToken);
            vector<string> courseInfo;
            while (getline(courseData, token, ','))
            {
                courseInfo.push_back(token);
            }
            if (courseInfo.size() >= 10)
            {
                string courseName = courseInfo[1];
                string professorName = courseInfo[2];
                string professorFamily = courseInfo[3];
                string college = courseInfo[4];
                string day = courseInfo[5];
                string time = courseInfo[6];
                int units = stoi(courseInfo[7]);
                int registeredS = stoi(courseInfo[8]);
                int capacity = stoi(courseInfo[9]);
                float score = stof(courseInfo[10]);
                float averageScore = stof(courseInfo[11]);
                Cours *course = new Cours(newStudent, courseName, college, professorName, professorFamily, units, capacity, day, time);
                course->set_score(score);
                course->set_registeredS(registeredS);
                course->set_average_Scores(averageScore);
                if (!headCourse)
                {
                    headCourse = course;
                }
                else
                {
                    Cours *tempCourse = headCourse;
                    while (tempCourse->get_next_cours())
                    {
                        tempCourse = tempCourse->get_next_cours();
                    }
                    tempCourse->set_next_cours(course);
                }
            }
        }
        newStudent->set_list_courses(headCourse);
        newStudent->set_nextS(headStudent);
        headStudent = newStudent;
    }
    inFile.close();
    return headStudent;
}

void save_professors(Professor *headProfessor)
{
    ofstream outFile("professors.csv");
    if (!outFile)
    {
        cerr << "Error opening file for writing." << endl;
        return;
    }
    Professor *temp = headProfessor;
    while (temp != nullptr)
    {
        outFile << temp->get_id() << "," << temp->get_firstname() << "," << temp->get_lastname() << ","<< temp->get_username() << "," << temp->get_password() << "," << temp->get_isActiveP() << ",";
        Cours *courses = temp->get_teachingCourse();
        while (courses != nullptr)
        {
            outFile << courses->get_id() << ","<< courses->get_Coursename() << ","
                    << courses->get_Professorname() << " " << courses->get_Professorfamaly() << ","<< courses->get_College() << ","
                    << courses->get_day() << "," << courses->get_time() << ","<< courses->get_units() << "," << courses->get_capacity() << ","
                    << courses->get_registeredS() << "," << courses->get_score() << ","<< courses->get_average_Scores() << ";";
            courses = courses->get_next_cours();
        }
        outFile << endl;
        temp = temp->get_nextP();
    }
    outFile.close();
}

Professor *load_professors(Student *all_students)
{
    ifstream inFile("professors.csv");
    if (!inFile)
    {
        cerr << "Error opening file for reading." << endl;
        return nullptr;
    }
    Professor *headProfessor = nullptr;
    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string token;
        vector<string> professorData;
        while (getline(ss, token, ','))
        {
            professorData.push_back(token);
        }
        int id = stoi(professorData[0]);
        string firstname = professorData[1];
        string lastname = professorData[2];
        string username = professorData[3];
        string password = professorData[4];
        bool isActive = professorData[5] == "1";
        Professor *newProfessor = new Professor(username, password, firstname, lastname, id);
        newProfessor->set_isActiveP(isActive);
        stringstream coursesStream(professorData[6]);
        string courseToken;
        Cours *headCourse = nullptr;
        while (getline(coursesStream, courseToken, ';'))
        {
            stringstream courseData(courseToken);
            vector<string> courseInfo;
            while (getline(courseData, token, ','))
            {
                courseInfo.push_back(token);
            }
            if (courseInfo.size() >= 10)
            {
                string courseName = courseInfo[1];
                string professorName = courseInfo[2];
                string professorFamily = courseInfo[3];
                string college = courseInfo[4];
                string day = courseInfo[5];
                string time = courseInfo[6];
                int units = stoi(courseInfo[7]);
                int capacity = stoi(courseInfo[8]);
                int registeredS = stoi(courseInfo[9]);
                float score = stof(courseInfo[10]);
                float averageScore = stof(courseInfo[11]);
                Cours *course = new Cours(all_students, courseName, college, professorName, professorFamily, units, capacity, day, time);
                course->set_score(score);
                course->set_registeredS(registeredS);
                course->set_average_Scores(averageScore);
                if (!headCourse)
                {
                    headCourse = course;
                }
                else
                {
                    Cours *tempCourse = headCourse;
                    while (tempCourse->get_next_cours())
                    {
                        tempCourse = tempCourse->get_next_cours();
                    }
                    tempCourse->set_next_cours(course);
                }
            }
        }
        newProfessor->set_teachingCourse(headCourse);
        newProfessor->set_nextP(headProfessor);
        headProfessor = newProfessor;
    }
    inFile.close();
    return headProfessor;
}

void save_courses(Cours *headCourse)
{
    ofstream outFile("courses.csv");
    if (!outFile)
    {
        cerr << "Error opening file for writing." << endl;
        return;
    }
    Cours *temp = headCourse;
    while (temp != nullptr)
    {
        outFile << temp->get_id() << ","
                << temp->get_Coursename() << ","
                << temp->get_Professorname() << " " << temp->get_Professorfamaly() << ","
                << temp->get_College() << ","
                << temp->get_day() << ","
                << temp->get_time() << ","
                << temp->get_units() << ","
                << temp->get_registeredS() << ","
                << temp->get_capacity() << ","
                << temp->get_score() << ","
                << temp->get_average_Scores() << ",";
        Task *tasks = temp->get_Tasks();
        while (tasks != nullptr)
        {
            outFile << tasks->get_nametask() << "," << tasks->get_description() << "," << tasks->get_deadline() << ";";
            Submission *submissions = tasks->get_Submissions();
            while (submissions != nullptr)
            {
                outFile << submissions->get_student_name() << "," << submissions->get_id() << "," << submissions->get_answer() << "," << submissions->get_score() << ";";
                submissions = submissions->get_next_sub();
            }
            tasks = tasks->get_next_task();
        }
        outFile << endl;
        temp = temp->get_next_cours();
    }

    outFile.close();
}

Cours *load_courses(Student *allStudents)
{
    ifstream inFile("courses.csv");
    if (!inFile)
    {
        cerr << "Error opening file for reading." << endl;
        return nullptr;
    }
    Cours *headCourse = nullptr;
    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string token;
        vector<string> courseData;
        while (getline(ss, token, ','))
        {
            courseData.push_back(token);
        }
        string courseName = courseData[1];
        string professorName = courseData[2];
        string professorFamily = courseData[3];
        string college = courseData[4];
        string day = courseData[5];
        string time = courseData[6];
        int units = stoi(courseData[7]);
        int registeredS = stoi(courseData[8]);
        int capacity = stoi(courseData[9]);
        float score = stof(courseData[10]);
        float averageScore = stof(courseData[11]);
        Cours *course = new Cours(allStudents, courseName, college, professorName, professorFamily, units, capacity, day, time);
        course->set_score(score);
        course->set_registeredS(registeredS);
        course->set_average_Scores(averageScore);
        stringstream tasksStream(courseData[12]);
        string taskToken;
        while (getline(tasksStream, taskToken, ';'))
        {
            stringstream taskData(taskToken);
            vector<string> taskInfo;
            while (getline(taskData, token, ','))
            {
                taskInfo.push_back(token);
            }
            if (taskInfo.size() >= 4)
            {
                string taskName = taskInfo[0];
                string taskDescription = taskInfo[1];
                string taskDeadline = taskInfo[2];
                Task *task = new Task(taskName, taskDescription, taskDeadline);
                stringstream submissionsStream(taskInfo[3]);
                string submissionToken;
                while (getline(submissionsStream, submissionToken, ';'))
                {
                    stringstream submissionData(submissionToken);
                    vector<string> submissionInfo;
                    while (getline(submissionData, token, ','))
                    {
                        submissionInfo.push_back(token);
                    }
                    if (submissionInfo.size() >= 4)
                    {
                        string studentName = submissionInfo[0];
                        int studentId = stoi(submissionInfo[1]);
                        string answer = submissionInfo[2];
                        float grad = stof(submissionInfo[3]);
                        task->Add_Submissions(studentName, studentId, answer);
                        task->get_Submissions()->set_score(grad);
                    }
                }
                course->Addtask(task);
            }
        }
        if (!headCourse)
        {
            headCourse = course;
        }
        else
        {
            Cours *tempCourse = headCourse;
            while (tempCourse->get_next_cours())
            {
                tempCourse = tempCourse->get_next_cours();
            }
            tempCourse->set_next_cours(course);
        }
    }
    inFile.close();
    return headCourse;
}
