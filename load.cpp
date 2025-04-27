#include "load.h"

Student *load_students()
{
    ifstream file("students.json");
    if (!file.is_open())
    {
        cerr << "Error: Could not open students.json" << endl;
        return nullptr;
    }

    json j;
    file >> j;
    file.close();

    Student *head = nullptr;
    Student *tail = nullptr;

    for (const auto &student_json : j["students"])
    {
        // ایجاد دانشجوی جدید
        Student *new_student = new Student(
            student_json["username"],
            student_json["password"],
            student_json["firstname"],
            student_json["lastname"],
            student_json["major"],
            student_json["id"]);
        new_student->set_isActiveS(student_json["isActive"]);

        // افزودن به لیست پیوندی
        if (!head)
        {
            head = tail = new_student;
        }
        else
        {
            tail->set_nextS(new_student);
            tail = new_student;
        }

        // بازیابی دروس دانشجو
        Cours *prev_course = nullptr;
        for (const auto &course_json : student_json["courses"])
        {
            Cours *new_course = new Cours(
                nullptr, // دانشجویان بعداً اضافه می‌شوند
                course_json["name"],
                course_json["college"],
                course_json["professor"]["firstname"],
                course_json["professor"]["lastname"],
                course_json["units"],
                course_json["capacity"],
                course_json["day"],
                course_json["time"]);
            new_course->set_id(course_json["id"]);
            new_course->set_registeredS(course_json["registered"]);
            new_course->set_score(course_json["score"]);
            new_course->set_average_Scores(course_json["average"]);

            // اضافه کردن اطلاعیه‌ها
            for (const auto &notice : course_json["notices"])
            {
                new_course->add_Notice(notice);
            }

            // اضافه کردن تکالیف
            for (const auto &task_json : course_json["tasks"])
            {
                Task *new_task = new Task(
                    task_json["name"],
                    task_json["description"],
                    task_json["deadline"]);
                new_course->Addtask(new_task);

                // اضافه کردن ارسال‌ها
                for (const auto &sub_json : task_json["submissions"])
                {
                    if (sub_json["student_id"] == new_student->get_id())
                    {
                        new_task->Add_Submissions(
                            new_student->get_firstname() + " " + new_student->get_lastname(),
                            sub_json["student_id"],
                            sub_json["answer"]);
                        Submission *sub = new_task->get_Submissions();
                        sub->set_score(sub_json["score"]);
                    }
                }
            }

            // اتصال دروس به دانشجو
            if (!new_student->get_list_courses())
            {
                new_student->set_list_courses(new_course);
                prev_course = new_course;
            }
            else
            {
                prev_course->set_next_cours(new_course);
                prev_course = new_course;
            }
        }
    }

    return head;
}
Professor *load_professors()
{
    ifstream file("professors.json");
    if (!file.is_open())
    {
        cerr << "Error: Could not open professors.json" << endl;
        return nullptr;
    }

    json j;
    file >> j;
    file.close();

    Professor *head = nullptr;
    Professor *tail = nullptr;

    for (const auto &professor_json : j["professors"])
    {
        // ایجاد استاد جدید
        Professor *new_professor = new Professor(
            professor_json["username"],
            professor_json["password"],
            professor_json["firstname"],
            professor_json["lastname"],
            professor_json["id"]);
        new_professor->set_isActiveP(professor_json["isActive"]);

        // افزودن به لیست پیوندی
        if (!head)
        {
            head = tail = new_professor;
        }
        else
        {
            tail->set_nextP(new_professor);
            tail = new_professor;
        }

        // بازیابی دروس استاد
        Cours *prev_course = nullptr;
        for (const auto &course_json : professor_json["courses"])
        {
            Cours *new_course = new Cours(
                nullptr, // دانشجویان بعداً اضافه می‌شوند
                course_json["name"],
                course_json["college"],
                professor_json["firstname"], // نام استاد از پروفایل استاد گرفته می‌شود
                professor_json["lastname"],
                course_json["units"],
                course_json["capacity"],
                course_json["day"],
                course_json["time"]);
            new_course->set_id(course_json["id"]);
            new_course->set_registeredS(course_json["registered"]);
            new_course->set_score(course_json["score"]);
            new_course->set_average_Scores(course_json["average"]);

            // اضافه کردن اطلاعیه‌ها
            for (const auto &notice : course_json["notices"])
            {
                new_course->add_Notice(notice);
            }

            // اضافه کردن نمره‌های دانشجویان
            for (const auto &[studentId, rating] : course_json["studentRatings"].items())
            {
                new_course->add_Student_rating(stoi(studentId), rating);
            }

            // اضافه کردن دانشجویان (فقط IDها)
            for (const auto &student_json : course_json["students"])
            {
                new_course->Addstudent(student_json["id"]);
            }

            // اضافه کردن تکالیف
            for (const auto &task_json : course_json["tasks"])
            {
                Task *new_task = new Task(
                    task_json["name"],
                    task_json["description"],
                    task_json["deadline"]);
                new_course->Addtask(new_task);

                // اضافه کردن ارسال‌ها
                for (const auto &sub_json : task_json["submissions"])
                {
                    new_task->Add_Submissions(
                        sub_json["student_name"],
                        sub_json["student_id"],
                        sub_json["answer"]);
                    Submission *sub = new_task->get_Submissions();
                    while (sub != nullptr && sub->get_id() != sub_json["student_id"])
                    {
                        sub = sub->get_next_sub();
                    }
                    if (sub)
                    {
                        sub->set_score(sub_json["score"]);
                    }
                }
            }

            // اتصال دروس به استاد
            if (!new_professor->get_teachingCourse())
            {
                new_professor->set_teachingCourse(new_course);
                prev_course = new_course;
            }
            else
            {
                prev_course->set_next_cours(new_course);
                prev_course = new_course;
            }
        }
    }

    return head;
}

Cours *load_courses(Student *all_students, Professor *all_professors)
{
    ifstream file("courses.json");
    if (!file.is_open())
    {
        cerr << "Error: Could not open courses.json" << endl;
        return nullptr;
    }

    json j;
    file >> j;
    file.close();

    Cours *head = nullptr;
    Cours *tail = nullptr;
    map<int, Cours *> course_map;

    // ایجاد دروس
    for (const auto &course_json : j["courses"])
    {
        Cours *new_course = new Cours(
            nullptr, // دانشجویان بعداً اضافه می‌شوند
            course_json["name"],
            course_json["college"],
            course_json["professor"]["firstname"],
            course_json["professor"]["lastname"],
            course_json["units"],
            course_json["capacity"],
            course_json["day"],
            course_json["time"]);
        new_course->set_id(course_json["id"]);
        new_course->set_registeredS(course_json["registered"]);
        new_course->set_score(course_json["score"]);
        new_course->set_average_Scores(course_json["average"]);

        // اضافه کردن اطلاعیه‌ها
        for (const auto &notice : course_json["notices"])
        {
            new_course->add_Notice(notice);
        }

        // اضافه کردن نمره‌های دانشجویان
        for (const auto &[student_id_str, rating] : course_json["studentRatings"].items())
        {
            int student_id = stoi(student_id_str);
            new_course->add_Student_rating(student_id, rating);
        }

        course_map[new_course->get_id()] = new_course;

        if (!head)
        {
            head = tail = new_course;
        }
        else
        {
            tail->set_next_cours(new_course);
            tail = new_course;
        }
    }

    // برقراری ارتباط با دانشجویان و اساتید
    for (const auto &course_json : j["courses"])
    {
        Cours *course = course_map[course_json["id"]];

        // اضافه کردن دانشجویان
        for (int student_id : course_json["students"])
        {
            Student *current = all_students;
            while (current != nullptr)
            {
                if (current->get_id() == student_id)
                {
                    course->Addstudent(student_id);
                    break;
                }
                current = current->get_nextS();
            }
        }

        // اضافه کردن تکالیف و ارسال‌ها
        for (const auto &task_json : course_json["tasks"])
        {
            Task *new_task = new Task(
                task_json["name"],
                task_json["description"],
                task_json["deadline"]);
            course->Addtask(new_task);

            for (const auto &sub_json : task_json["submissions"])
            {
                Student *student = nullptr;
                Student *current = all_students;
                while (current != nullptr)
                {
                    if (current->get_id() == sub_json["student_id"])
                    {
                        student = current;
                        break;
                    }
                    current = current->get_nextS();
                }

                if (student)
                {
                    new_task->Add_Submissions(
                        sub_json["student_name"],
                        sub_json["student_id"],
                        sub_json["answer"]);
                    Submission *sub = new_task->get_Submissions();
                    while (sub != nullptr && sub->get_id() != sub_json["student_id"])
                    {
                        sub = sub->get_next_sub();
                    }
                    if (sub)
                    {
                        sub->set_score(sub_json["score"]);
                    }
                }
            }
        }
    }

    return head;
}
