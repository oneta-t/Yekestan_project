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
    int lineNum = 0;

    while (getline(inFile, line))
    {
        lineNum++;
        stringstream ss(line);
        string token;
        vector<string> studentData;

        try
        {
            while (getline(ss, token, ','))
            {
                studentData.push_back(token);
            }

            if (studentData.size() < 7)
            {
                cerr << "Warning in line " << lineNum << ": Missing required fields (found " << studentData.size() << " fields, expected at least 7)" << endl;
                continue;
            }

            int id = stoi(studentData[0]);
            bool isActive = studentData[6] == "1";

            Student *newStudent = new Student(
                studentData[4],
                studentData[5], 
                studentData[1], 
                studentData[2],
                studentData[3], 
                id);
            newStudent->set_isActiveS(isActive);

            if (studentData.size() > 7 && !studentData[7].empty())
            {
                stringstream coursesStream(studentData[7]);
                string courseToken;
                Cours *headCourse = nullptr;

                while (getline(coursesStream, courseToken, ';'))
                {
                    try
                    {
                        vector<string> courseInfo;
                        stringstream courseData(courseToken);

                        while (getline(courseData, token, ','))
                        {
                            courseInfo.push_back(token);
                        }
                        if (courseInfo.size() < 12)
                        {
                            cerr << "Warning: Skipping incomplete course in line " << lineNum << endl;
                            continue;
                        }
                        if (courseInfo.size() >= 12)
                        {
                            Cours *course = new Cours(
                                newStudent,
                                courseInfo[1],       
                                courseInfo[4],       
                                courseInfo[2],       
                                courseInfo[3],       
                                stoi(courseInfo[7]), 
                                stoi(courseInfo[9]), 
                                courseInfo[5],       
                                courseInfo[6]       
                            );

                            course->set_score(stof(courseInfo[10]));
                            course->set_registeredS(stoi(courseInfo[8]));
                            course->set_average_Scores(stof(courseInfo[11]));

                            if (!headCourse)
                            {
                                headCourse = course;
                            }
                            else
                            {
                                Cours *temp = headCourse;
                                while (temp->get_next_cours())
                                {
                                    temp = temp->get_next_cours();
                                }
                                temp->set_next_cours(course);
                            }
                        }
                        else
                        {
                            cerr << "Warning in line " << lineNum
                                 << ": Incomplete course data (found "
                                 << courseInfo.size() << " fields)" << endl;
                        }
                    }
                    catch (const exception &e)
                    {
                        cerr << "Error processing course in line " << lineNum
                             << ": " << e.what() << endl;
                    }
                }
                newStudent->set_list_courses(headCourse);
            }

            newStudent->set_nextS(headStudent);
            headStudent = newStudent;
        }
        catch (const exception &e)
        {
            cerr << "Error processing student in line " << lineNum
                 << ": " << e.what() << endl;
            continue;
        }
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
        outFile << temp->get_id() << "," << temp->get_firstname() << "," << temp->get_lastname() << "," << temp->get_username() << "," << temp->get_password() << "," << temp->get_isActiveP() << ",";
        Cours *courses = temp->get_teachingCourse();
        while (courses != nullptr)
        {
            outFile << courses->get_id() << "," << courses->get_Coursename() << ","
                    << courses->get_Professorname() << " " << courses->get_Professorfamaly() << "," << courses->get_College() << ","
                    << courses->get_day() << "," << courses->get_time() << "," << courses->get_units() << "," << courses->get_capacity() << ","
                    << courses->get_registeredS() << "," << courses->get_score() << "," << courses->get_average_Scores() << ";";
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
    int lineNum = 0;

    while (getline(inFile, line))
    {
        lineNum++;
        stringstream ss(line);
        string token;
        vector<string> professorData;

        try
        {
            while (getline(ss, token, ','))
            {
                professorData.push_back(token);
            }

            if (professorData.size() < 6)
            {
                cerr << "Warning in line " << lineNum << ": Missing required fields (found "
                     << professorData.size() << " fields, expected at least 6)" << endl;
                continue;
            }

            int id = stoi(professorData[0]);
            bool isActive = professorData[5] == "1";

            Professor *newProfessor = new Professor(
                professorData[3], 
                professorData[4], 
                professorData[1], 
                professorData[2], 
                id);
            newProfessor->set_isActiveP(isActive);

            if (professorData.size() > 6 && !professorData[6].empty())
            {
                stringstream coursesStream(professorData[6]);
                string courseToken;
                Cours *headCourse = nullptr;

                while (getline(coursesStream, courseToken, ';'))
                {
                    try
                    {
                        vector<string> courseInfo;
                        stringstream courseData(courseToken);

                        while (getline(courseData, token, ','))
                        {
                            courseInfo.push_back(token);
                        }

                        if (courseInfo.size() >= 12)
                        { 
                            Cours *course = new Cours(
                                all_students,
                                courseInfo[1],       
                                courseInfo[4],       
                                courseInfo[2],       
                                courseInfo[3],      
                                stoi(courseInfo[7]), 
                                stoi(courseInfo[8]), 
                                courseInfo[5],       
                                courseInfo[6]   
                            );

                            course->set_score(stof(courseInfo[10]));
                            course->set_registeredS(stoi(courseInfo[9]));
                            course->set_average_Scores(stof(courseInfo[11]));

                            if (!headCourse)
                            {
                                headCourse = course;
                            }
                            else
                            {
                                Cours *temp = headCourse;
                                while (temp->get_next_cours())
                                {
                                    temp = temp->get_next_cours();
                                }
                                temp->set_next_cours(course);
                            }
                        }
                        else
                        {
                            cerr << "Warning in line " << lineNum
                                 << ": Incomplete course data (found "
                                 << courseInfo.size() << " fields)" << endl;
                        }
                    }
                    catch (const exception &e)
                    {
                        cerr << "Error processing course in line " << lineNum
                             << ": " << e.what() << endl;
                    }
                }
                newProfessor->set_teachingCourse(headCourse);
            }

            newProfessor->set_nextP(headProfessor);
            headProfessor = newProfessor;
        }
        catch (const exception &e)
        {
            cerr << "Error processing professor in line " << lineNum
                 << ": " << e.what() << endl;
            continue;
        }
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
                << temp->get_Professorname() << ","
                << temp->get_Professorfamaly() << ","
                << temp->get_College() << ","
                << temp->get_day() << ","
                << temp->get_time() << ","
                << temp->get_units() << ","
                << temp->get_registeredS() << ","
                << temp->get_capacity() << ","
                << temp->get_score() << ","
                << temp->get_average_Scores();

        Task *tasks = temp->get_Tasks();
        while (tasks != nullptr)
        {
            outFile << "|T|" << tasks->get_nametask() << ","
                    << tasks->get_description() << ","
                    << tasks->get_deadline();

            Submission *submissions = tasks->get_Submissions();
            while (submissions != nullptr)
            {
                outFile << "|S|" << submissions->get_student_name() << ","
                        << submissions->get_id() << ","
                        << submissions->get_answer() << ","
                        << submissions->get_score();
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
        vector<string> mainFields;
        string field;

        while (getline(ss, field, ','))
        {
            mainFields.push_back(field);
        }

        if (mainFields.size() < 12)
        {
            cerr << "Warning: Incomplete course data, skipping line" << endl;
            continue;
        }

        Cours *course = new Cours(
            allStudents,
            mainFields[1],       
            mainFields[4],       
            mainFields[2],
            mainFields[3],       
            stoi(mainFields[7]),
            stoi(mainFields[9]),
            mainFields[5],       
            mainFields[6]  
        );

        course->set_id(stoi(mainFields[0]));
        course->set_registeredS(stoi(mainFields[8]));
        course->set_score(stof(mainFields[10]));
        course->set_average_Scores(stof(mainFields[11]));

        if (mainFields.size() > 12)
        {
            string remainingData = mainFields[12];
            size_t taskPos = remainingData.find("|T|");

            while (taskPos != string::npos)
            {
                size_t nextTaskPos = remainingData.find("|T|", taskPos + 1);
                string taskData = remainingData.substr(taskPos + 3,(nextTaskPos == string::npos) ? string::npos : nextTaskPos - (taskPos + 3));

                vector<string> taskFields;
                stringstream taskStream(taskData);
                while (getline(taskStream, field, ','))
                {
                    taskFields.push_back(field);
                }

                if (taskFields.size() >= 3)
                {
                    Task *task = new Task(
                        taskFields[0], 
                        taskFields[1], 
                        taskFields[2]  
                    );

                    size_t subPos = taskData.find("|S|");
                    while (subPos != string::npos)
                    {
                        size_t nextSubPos = taskData.find("|S|", subPos + 1);
                        string subData = taskData.substr(subPos + 3,(nextSubPos == string::npos) ? string::npos : nextSubPos - (subPos + 3));

                        vector<string> subFields;
                        stringstream subStream(subData);
                        while (getline(subStream, field, ','))
                        {
                            subFields.push_back(field);
                        }

                        if (subFields.size() >= 4)
                        {
                            task->Add_Submissions(
                                subFields[0],   
                                stoi(subFields[1]), 
                                subFields[2]     
                            );
                            task->get_Submissions()->set_score(stof(subFields[3])); 
                        }
                        subPos = nextSubPos;
                    }
                    course->Addtask(task);
                }

                taskPos = nextTaskPos;
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