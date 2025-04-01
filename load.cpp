#include "load.h"

Student *load_students_with_courses()
{
    ifstream file("student.json");
    if (!file.is_open())
    {
        cerr << "Error opening file!" << endl;
        return nullptr;
    }
    json j;
    file >> j;
    file.close();
    Student *head = nullptr;
    Student *tail = nullptr;
    for (auto &student_data : j["students"])
    {
        Student *new_student = new Student(
            student_data["username"],
            student_data["password"],
            student_data["firstname"],
            student_data["lastname"],
            student_data["major"],
            student_data["id"]);
        new_student->set_isActiveS(student_data["isActive"]);

        for (auto &course_data : student_data["courses"])
        {
            Cours *new_course = new Cours(
                course_data["name"],
                course_data["college"],
                course_data["professor"]["firstname"],
                course_data["professor"]["lastname"],
                course_data["units"],
                course_data["capacity"],
                course_data["score"],
                course_data["average"],
                course_data["time"]["day"],
                course_data["time"]["hour"]);
            new_course->set_id(course_data["id"]);
            new_course->set_Notice(course_data["notice"]);

            for (auto &task_data : course_data["tasks"])
            {
                Task *new_task = new Task(
                    task_data["name"],
                    task_data["description"],
                    task_data["deadline"]);

                for (auto &sub_data : task_data["submissions"])
                {
                    new_task->Add_Submissions(
                        sub_data["student_name"],
                        sub_data["student_id"],
                        sub_data["answer"]);
                    Submission *sub = new_task->get_Submissions();
                    if (sub->get_id() == sub_data["student_id"])
                    {
                        sub->set_score(sub_data["score"]);
                        break;
                    }
                }

                new_course->Addtask(new_task);
            }

            new_course->set_next_cours(new_student->get_list_courses());
            new_student->set_list_courses(new_course);
        }

        if (!head)
            head = new_student;
        else
            tail->set_nextS(new_student);
        tail = new_student;
    }
    return head;
}

Professor *load_professors(Student *all_students)
{
    ifstream file("professor.json");
    if (!file.is_open())
    {
        cerr << "Error opening file!" << endl;
        return nullptr;
    }
    json j;
    file >> j;
    file.close();
    Professor *head = nullptr;
    Professor *tail = nullptr;
    for (auto &prof_data : j["professors"])
    {
        Professor *new_prof = new Professor(
            prof_data["username"],
            prof_data["password"],
            prof_data["firstname"],
            prof_data["lastname"],
            prof_data["id"]);
        new_prof->set_isActiveP(prof_data["isActive"]);

        for (auto &course_data : prof_data["courses"])
        {
            Cours *new_course = new Cours(
                course_data["name"],
                course_data["college"],
                prof_data["firstname"],
                prof_data["lastname"],
                course_data["units"],
                course_data["capacity"],
                0,
                0,
                course_data["day"],
                course_data["time"]);
            new_course->set_id(course_data["id"]);
            new_course->set_Notice(course_data["notice"]);

            for (auto &student_data : course_data["students"])
            {
                Student *student = find_student_by_id(all_students, student_data["id"]);
                if (student)
                {
                    new_course->Addstudent(student);
                    // اضافه کردن درس به لیست درس‌های دانشجو
                    new_course->set_next_cours(student->get_list_courses());
                    student->set_list_courses(new_course);
                }
            }

            // بارگذاری تمرین‌های این درس
            for (auto &task_data : course_data["tasks"])
            {
                Task *new_task = new Task(
                    task_data["name"],
                    task_data["description"],
                    task_data["deadline"]);

                // بارگذاری پاسخ‌های این تمرین
                for (auto &sub_data : task_data["submissions"])
                {
                    new_task->Add_Submissions(
                        "", // نام دانشجو بعداً تنظیم می‌شود
                        sub_data["student_id"],
                        sub_data["answer"]);
                    // تنظیم نمره
                    Submission *sub = new_task->get_Submissions();
                    if (sub->get_id() == sub_data["student_id"])
                    {
                        sub->set_score(sub_data["score"]);
                        // پیدا کردن نام دانشجو
                        Student *s = find_student_by_id(all_students, sub_data["student_id"]);
                        if (s)
                        {
                            sub->set_student_name(s->get_firstname() + " " + s->get_lastname());
                        }
                        break;
                    }
                }

                new_course->Addtask(new_task);
            }

            // اضافه کردن درس به لیست درس‌های استاد
            new_course->set_next_cours(new_prof->get_teachingCourse());
            new_prof->set_teachingCourse(new_course);
        }

        if (!head)
            head = new_prof;
        else
            tail->set_nextP(new_prof);
        tail = new_prof;
    }

    return head;
}

Student *find_student_by_id(Student *head, int id)
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

Cours* load_courses()
{
    ifstream file("course.json");
    if (!file.is_open())
    {
        cerr << "Error opening courses file!" << endl;
        return nullptr;
    }

    json j;
    try
    {
        file >> j;
    }
    catch (const exception &e)
    {
        cerr << "JSON parsing error: " << e.what() << endl;
        file.close();
        return nullptr;
    }
    file.close();

    Cours *head = nullptr;
    Cours *tail = nullptr;
    unordered_map<int, Student *> student_map; // برای جلوگیری از ایجاد دانشجوهای تکراری

    for (auto &course_data : j["courses"])
    {
        try
        {
            // ایجاد درس جدید
            Cours *new_course = new Cours(
                course_data["name"],
                course_data["college"],
                course_data["professor"]["firstname"],
                course_data["professor"]["lastname"],
                course_data["units"],
                course_data["capacity"],
                course_data["score"],
                course_data["average"],
                course_data["day"],
                course_data["time"]);
            new_course->set_id(course_data["id"]);
            new_course->set_registeredS(course_data["registered"]);
            new_course->set_Notice(course_data["notice"]);

            // بارگذاری دانشجوها با اطلاعات کامل
            Student *last_student = nullptr;
            for (auto &student_data : course_data["students"])
            {
                int student_id = student_data["id"];

                // اگر دانشجو از قبل وجود ندارد، ایجاد می‌کنیم
                if (student_map.find(student_id) == student_map.end())
                {
                    Student *new_student = new Student(
                        student_data["username"],
                        student_data["password"],
                        student_data["firstname"],
                        student_data["lastname"],
                        student_data["major"],
                        student_id);
                    new_student->set_isActiveS(student_data["isActive"]);
                    student_map[student_id] = new_student;
                }

                // اضافه کردن دانشجو به درس
                if (last_student == nullptr)
                {
                    new_course->set_Students(student_map[student_id]);
                }
                else
                {
                    last_student->set_nextS(student_map[student_id]);
                }
                last_student = student_map[student_id];

                // برقراری رابطه دوطرفه (اضافه کردن درس به دانشجو)
                new_course->set_next_cours(student_map[student_id]->get_list_courses());
                student_map[student_id]->set_list_courses(new_course);
            }

            // بارگذاری تمرین‌ها و پاسخ‌ها (مشابه قبل)
            Task *last_task = nullptr;
            for (auto &task_data : course_data["tasks"])
            {
                Task *new_task = new Task(
                    task_data["name"],
                    task_data["description"],
                    task_data["deadline"]);

                // بارگذاری پاسخ‌ها
                Submission *last_submission = nullptr;
                for (auto &sub_data : task_data["submissions"])
                {
                    int student_id = sub_data["student_id"];
                    if (student_map.find(student_id) != student_map.end())
                    {
                        Submission *new_sub = new Submission(
                            student_id,
                            student_map[student_id]->get_firstname() + " " +
                                student_map[student_id]->get_lastname(),
                            sub_data["answer"],
                            sub_data["score"]);

                        if (last_submission == nullptr)
                        {
                            new_task->set_Submissions(new_sub);
                        }
                        else
                        {
                            last_submission->set_next_sub(new_sub);
                        }
                        last_submission = new_sub;
                    }
                }

                // اضافه کردن تمرین به درس
                if (last_task == nullptr)
                {
                    new_course->set_Tasks(new_task);
                }
                else
                {
                    last_task->set_next_task(new_task);
                }
                last_task = new_task;
            }

            // اضافه کردن درس به لیست
            if (head == nullptr)
            {
                head = new_course;
            }
            else
            {
                tail->set_next_cours(new_course);
            }
            tail = new_course;
        }
        catch (const exception &e)
        {
            cerr << "Error loading course: " << e.what() << endl;
            continue;
        }
    }

    return head;
}
