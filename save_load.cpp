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

// Student *load_students()
// {
//     ifstream inFile("students.csv");
//     if (!inFile)
//     {
//         cerr << "Error opening file for reading." << endl;
//         return nullptr;
//     }
//     Student *headStudent = nullptr;
//     string line;
//     while (getline(inFile, line))
//     {
//         stringstream ss(line);
//         string token;
//         vector<string> studentData;
//         while (getline(ss, token, ','))
//         {
//             studentData.push_back(token);
//         }
//         int id = stoi(studentData[0]);
//         string firstname = studentData[1];
//         string lastname = studentData[2];
//         string major = studentData[3];
//         string username = studentData[4];
//         string password = studentData[5];
//         bool isActive = studentData[6] == "1";
//         Student *newStudent = new Student(username, password, firstname, lastname, major, id);
//         newStudent->set_isActiveS(isActive);
//         stringstream coursesStream(studentData[7]);
//         string courseToken;
//         Cours *headCourse = nullptr;
//         while (getline(coursesStream, courseToken, ';'))
//         {
//             stringstream courseData(courseToken);
//             vector<string> courseInfo;
//             while (getline(courseData, token, ','))
//             {
//                 courseInfo.push_back(token);
//             }
//             if (courseInfo.size() >= 10)
//             {
//                 string courseName = courseInfo[1];
//                 string professorName = courseInfo[2];
//                 string professorFamily = courseInfo[3];
//                 string college = courseInfo[4];
//                 string day = courseInfo[5];
//                 string time = courseInfo[6];
//                 int units = stoi(courseInfo[7]);
//                 int registeredS = stoi(courseInfo[8]);
//                 int capacity = stoi(courseInfo[9]);
//                 float score = stof(courseInfo[10]);
//                 float averageScore = stof(courseInfo[11]);
//                 Cours *course = new Cours(newStudent, courseName, college, professorName, professorFamily, units, capacity, day, time);
//                 course->set_score(score);
//                 course->set_registeredS(registeredS);
//                 course->set_average_Scores(averageScore);
//                 if (!headCourse)
//                 {
//                     headCourse = course;
//                 }
//                 else
//                 {
//                     Cours *tempCourse = headCourse;
//                     while (tempCourse->get_next_cours())
//                     {
//                         tempCourse = tempCourse->get_next_cours();
//                     }
//                     tempCourse->set_next_cours(course);
//                 }
//             }
//         }
//         newStudent->set_list_courses(headCourse);
//         newStudent->set_nextS(headStudent);
//         headStudent = newStudent;
//     }
//     inFile.close();
//     return headStudent;
// }

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
            // خواندن و بررسی داده‌های پایه دانشجو
            while (getline(ss, token, ','))
            {
                studentData.push_back(token);
            }

            // بررسی حداقل فیلدهای مورد نیاز
            if (studentData.size() < 7)
            {
                cerr << "Warning in line " << lineNum << ": Missing required fields (found "
                     << studentData.size() << " fields, expected at least 7)" << endl;
                continue;
            }

            // تبدیل و اعتبارسنجی فیلدهای اجباری
            int id = stoi(studentData[0]);
            bool isActive = studentData[6] == "1";

            // ایجاد دانشجو
            Student *newStudent = new Student(
                studentData[4], // username
                studentData[5], // password
                studentData[1], // firstname
                studentData[2], // lastname
                studentData[3], // major
                id);
            newStudent->set_isActiveS(isActive);

            // پردازش اختیاری دروس (اگر وجود دارد)
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
                            continue; // فقط این درس حذف می‌شود، نه کل دانشجو
                        }
                        // بررسی کامل بودن اطلاعات دوره
                        if (courseInfo.size() >= 12)
                        { // 12 فیلد مورد نیاز
                            Cours *course = new Cours(
                                newStudent,
                                courseInfo[1],       // courseName
                                courseInfo[4],       // college
                                courseInfo[2],       // professorName
                                courseInfo[3],       // professorFamily
                                stoi(courseInfo[7]), // units
                                stoi(courseInfo[9]), // capacity
                                courseInfo[5],       // day
                                courseInfo[6]        // time
                            );

                            // تنظیم اطلاعات اضافی
                            course->set_score(stof(courseInfo[10]));
                            course->set_registeredS(stoi(courseInfo[8]));
                            course->set_average_Scores(stof(courseInfo[11]));

                            // افزودن به لیست دروس
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

            // افزودن دانشجو به لیست
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

// Professor *load_professors(Student *all_students)
// {
//     ifstream inFile("professors.csv");
//     if (!inFile)
//     {
//         cerr << "Error opening file for reading." << endl;
//         return nullptr;
//     }
//     Professor *headProfessor = nullptr;
//     string line;
//     while (getline(inFile, line))
//     {
//         stringstream ss(line);
//         string token;
//         vector<string> professorData;
//         while (getline(ss, token, ','))
//         {
//             professorData.push_back(token);
//         }
//         int id = stoi(professorData[0]);
//         string firstname = professorData[1];
//         string lastname = professorData[2];
//         string username = professorData[3];
//         string password = professorData[4];
//         bool isActive = professorData[5] == "1";
//         Professor *newProfessor = new Professor(username, password, firstname, lastname, id);
//         newProfessor->set_isActiveP(isActive);
//         stringstream coursesStream(professorData[6]);
//         string courseToken;
//         Cours *headCourse = nullptr;
//         while (getline(coursesStream, courseToken, ';'))
//         {
//             stringstream courseData(courseToken);
//             vector<string> courseInfo;
//             while (getline(courseData, token, ','))
//             {
//                 courseInfo.push_back(token);
//             }
//             if (courseInfo.size() >= 10)
//             {
//                 string courseName = courseInfo[1];
//                 string professorName = courseInfo[2];
//                 string professorFamily = courseInfo[3];
//                 string college = courseInfo[4];
//                 string day = courseInfo[5];
//                 string time = courseInfo[6];
//                 int units = stoi(courseInfo[7]);
//                 int capacity = stoi(courseInfo[8]);
//                 int registeredS = stoi(courseInfo[9]);
//                 float score = stof(courseInfo[10]);
//                 float averageScore = stof(courseInfo[11]);
//                 Cours *course = new Cours(all_students, courseName, college, professorName, professorFamily, units, capacity, day, time);
//                 course->set_score(score);
//                 course->set_registeredS(registeredS);
//                 course->set_average_Scores(averageScore);
//                 if (!headCourse)
//                 {
//                     headCourse = course;
//                 }
//                 else
//                 {
//                     Cours *tempCourse = headCourse;
//                     while (tempCourse->get_next_cours())
//                     {
//                         tempCourse = tempCourse->get_next_cours();
//                     }
//                     tempCourse->set_next_cours(course);
//                 }
//             }
//         }
//         newProfessor->set_teachingCourse(headCourse);
//         newProfessor->set_nextP(headProfessor);
//         headProfessor = newProfessor;
//     }
//     inFile.close();
//     return headProfessor;
// }

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
            // خواندن و بررسی داده‌های پایه استاد
            while (getline(ss, token, ','))
            {
                professorData.push_back(token);
            }

            // بررسی حداقل فیلدهای مورد نیاز
            if (professorData.size() < 6)
            {
                cerr << "Warning in line " << lineNum << ": Missing required fields (found "
                     << professorData.size() << " fields, expected at least 6)" << endl;
                continue;
            }

            // تبدیل و اعتبارسنجی فیلدهای اجباری
            int id = stoi(professorData[0]);
            bool isActive = professorData[5] == "1";

            // ایجاد استاد
            Professor *newProfessor = new Professor(
                professorData[3], // username
                professorData[4], // password
                professorData[1], // firstname
                professorData[2], // lastname
                id);
            newProfessor->set_isActiveP(isActive);

            // پردازش اختیاری دروس (اگر وجود دارد)
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

                        // بررسی کامل بودن اطلاعات دوره
                        if (courseInfo.size() >= 12)
                        { // 12 فیلد مورد نیاز
                            Cours *course = new Cours(
                                all_students,
                                courseInfo[1],       // courseName
                                courseInfo[4],       // college
                                courseInfo[2],       // professorName
                                courseInfo[3],       // professorFamily
                                stoi(courseInfo[7]), // units
                                stoi(courseInfo[8]), // capacity
                                courseInfo[5],       // day
                                courseInfo[6]        // time
                            );

                            // تنظیم اطلاعات اضافی
                            course->set_score(stof(courseInfo[10]));
                            course->set_registeredS(stoi(courseInfo[9]));
                            course->set_average_Scores(stof(courseInfo[11]));

                            // افزودن به لیست دروس
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

            // افزودن استاد به لیست
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

// void save_courses(Cours *headCourse)
// {
//     ofstream outFile("courses.csv");
//     if (!outFile)
//     {
//         cerr << "Error opening file for writing." << endl;
//         return;
//     }
//     Cours *temp = headCourse;
//     while (temp != nullptr)
//     {
//         outFile << temp->get_id() << ","
//                 << temp->get_Coursename() << ","
//                 << temp->get_Professorname() << " " << temp->get_Professorfamaly() << ","
//                 << temp->get_College() << ","
//                 << temp->get_day() << ","
//                 << temp->get_time() << ","
//                 << temp->get_units() << ","
//                 << temp->get_registeredS() << ","
//                 << temp->get_capacity() << ","
//                 << temp->get_score() << ","
//                 << temp->get_average_Scores() << ",";
//         Task *tasks = temp->get_Tasks();
//         while (tasks != nullptr)
//         {
//             outFile << tasks->get_nametask() << "," << tasks->get_description() << "," << tasks->get_deadline() << ";";
//             Submission *submissions = tasks->get_Submissions();
//             while (submissions != nullptr)
//             {
//                 outFile << submissions->get_student_name() << "," << submissions->get_id() << "," << submissions->get_answer() << "," << submissions->get_score() << ";";
//                 submissions = submissions->get_next_sub();
//             }
//             tasks = tasks->get_next_task();
//         }
//         outFile << endl;
//         temp = temp->get_next_cours();
//     }

//     outFile.close();
// }

// Cours *load_courses(Student *allStudents)
// {
//     ifstream inFile("courses.csv");
//     if (!inFile)
//     {
//         cerr << "Error opening file for reading." << endl;
//         return nullptr;
//     }
//     Cours *headCourse = nullptr;
//     string line;
//     while (getline(inFile, line))
//     {
//         stringstream ss(line);
//         string token;
//         vector<string> courseData;
//         while (getline(ss, token, ','))
//         {
//             courseData.push_back(token);
//         }
//         string courseName = courseData[1];
//         string professorName = courseData[2];
//         string professorFamily = courseData[3];
//         string college = courseData[4];
//         string day = courseData[5];
//         string time = courseData[6];
//         int units = stoi(courseData[7]);
//         int registeredS = stoi(courseData[8]);
//         int capacity = stoi(courseData[9]);
//         float score = stof(courseData[10]);
//         float averageScore = stof(courseData[11]);
//         Cours *course = new Cours(allStudents, courseName, college, professorName, professorFamily, units, capacity, day, time);
//         course->set_score(score);
//         course->set_registeredS(registeredS);
//         course->set_average_Scores(averageScore);
//         stringstream tasksStream(courseData[12]);
//         string taskToken;
//         while (getline(tasksStream, taskToken, ';'))
//         {
//             stringstream taskData(taskToken);
//             vector<string> taskInfo;
//             while (getline(taskData, token, ','))
//             {
//                 taskInfo.push_back(token);
//             }
//             if (taskInfo.size() >= 4)
//             {
//                 string taskName = taskInfo[0];
//                 string taskDescription = taskInfo[1];
//                 string taskDeadline = taskInfo[2];
//                 Task *task = new Task(taskName, taskDescription, taskDeadline);
//                 stringstream submissionsStream(taskInfo[3]);
//                 string submissionToken;
//                 while (getline(submissionsStream, submissionToken, ';'))
//                 {
//                     stringstream submissionData(submissionToken);
//                     vector<string> submissionInfo;
//                     while (getline(submissionData, token, ','))
//                     {
//                         submissionInfo.push_back(token);
//                     }
//                     if (submissionInfo.size() >= 4)
//                     {
//                         string studentName = submissionInfo[0];
//                         int studentId = stoi(submissionInfo[1]);
//                         string answer = submissionInfo[2];
//                         float grad = stof(submissionInfo[3]);
//                         task->Add_Submissions(studentName, studentId, answer);
//                         task->get_Submissions()->set_score(grad);
//                     }
//                 }
//                 course->Addtask(task);
//             }
//         }
//         if (!headCourse)
//         {
//             headCourse = course;
//         }
//         else
//         {
//             Cours *tempCourse = headCourse;
//             while (tempCourse->get_next_cours())
//             {
//                 tempCourse = tempCourse->get_next_cours();
//             }
//             tempCourse->set_next_cours(course);
//         }
//     }
//     inFile.close();
//     return headCourse;
// }
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
        // ذخیره اطلاعات پایه درس
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

        // ذخیره tasks
        Task *tasks = temp->get_Tasks();
        while (tasks != nullptr)
        {
            outFile << "|T|" << tasks->get_nametask() << ","
                    << tasks->get_description() << ","
                    << tasks->get_deadline();

            // ذخیره submissions
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

        // خواندن فیلدهای اصلی
        while (getline(ss, field, ','))
        {
            mainFields.push_back(field);
        }

        // بررسی حداقل فیلدهای مورد نیاز
        if (mainFields.size() < 12)
        {
            cerr << "Warning: Incomplete course data, skipping line" << endl;
            continue;
        }

        // ایجاد شیء درس
        Cours *course = new Cours(
            allStudents,
            mainFields[1],       // نام درس
            mainFields[4],       // دانشکده
            mainFields[2],       // نام استاد
            mainFields[3],       // نام خانوادگی استاد
            stoi(mainFields[7]), // واحدها
            stoi(mainFields[9]), // ظرفیت
            mainFields[5],       // روزها
            mainFields[6]        // زمان
        );

        // تنظیم سایر ویژگی‌ها
        course->set_id(stoi(mainFields[0]));
        course->set_registeredS(stoi(mainFields[8]));
        course->set_score(stof(mainFields[10]));
        course->set_average_Scores(stof(mainFields[11]));

        // پردازش tasks و submissions (اگر وجود دارند)
        if (mainFields.size() > 12)
        {
            string remainingData = mainFields[12];
            size_t taskPos = remainingData.find("|T|");

            while (taskPos != string::npos)
            {
                size_t nextTaskPos = remainingData.find("|T|", taskPos + 1);
                string taskData = remainingData.substr(taskPos + 3,
                                                       (nextTaskPos == string::npos) ? string::npos : nextTaskPos - (taskPos + 3));

                // پردازش task
                vector<string> taskFields;
                stringstream taskStream(taskData);
                while (getline(taskStream, field, ','))
                {
                    taskFields.push_back(field);
                }

                if (taskFields.size() >= 3)
                {
                    Task *task = new Task(
                        taskFields[0], // نام تسک
                        taskFields[1], // توضیحات
                        taskFields[2]  // مهلت
                    );

                    // پردازش submissions
                    size_t subPos = taskData.find("|S|");
                    while (subPos != string::npos)
                    {
                        size_t nextSubPos = taskData.find("|S|", subPos + 1);
                        string subData = taskData.substr(subPos + 3,
                                                         (nextSubPos == string::npos) ? string::npos : nextSubPos - (subPos + 3));

                        vector<string> subFields;
                        stringstream subStream(subData);
                        while (getline(subStream, field, ','))
                        {
                            subFields.push_back(field);
                        }

                        if (subFields.size() >= 4)
                        {
                            task->Add_Submissions(
                                subFields[0],       // نام دانشجو
                                stoi(subFields[1]), // ID دانشجو
                                subFields[2]        // پاسخ
                            );
                            task->get_Submissions()->set_score(stof(subFields[3])); // نمره
                        }

                        subPos = nextSubPos;
                    }

                    course->Addtask(task);
                }

                taskPos = nextTaskPos;
            }
        }

        // اضافه کردن درس به لیست
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