#include "save.h"

void save_students(Student *head)
{
    json j;
    j["students"] = json::array();

    Student *current_student = head;
    while (current_student != nullptr)
    {
        json student_json = {
            {"username", current_student->get_username()},
            {"password", current_student->get_password()},
            {"firstname", current_student->get_firstname()},
            {"lastname", current_student->get_lastname()},
            {"major", current_student->get_major()},
            {"id", current_student->get_id()},
            {"isActive", current_student->get_isActiveS()}};

        json courses_json = json::array();
        Cours *current_course = current_student->get_list_courses();
        while (current_course != nullptr)
        {
            json course_json = {
                {"id", current_course->get_id()},
                {"name", current_course->get_Coursename()},
                {"college", current_course->get_College()},
                {"professor", {{"firstname", current_course->get_Professorname()}, {"lastname", current_course->get_Professorfamaly()}}},
                {"units", current_course->get_units()},
                {"time", {{"day", current_course->get_day()}, {"hour", current_course->get_time()}}},
                {"score", current_course->get_score()},
                {"average", current_course->get_average_Scores()},
                {"notice", current_course->get_Notice()}};

            json tasks_json = json::array();
            Task *current_task = current_course->get_Tasks();
            while (current_task != nullptr)
            {
                json task_json = {
                    {"name", current_task->get_nametask()},
                    {"description", current_task->get_description()},
                    {"deadline", current_task->get_deadline()}};

                json submissions_json = json::array();
                Submission *current_sub = current_task->get_Submissions();
                submissions_json.push_back({{"student_id", current_sub->get_id()},
                                            {"student_name", current_sub->get_student_name()},
                                            {"answer", current_sub->get_answer()},
                                            {"score", current_sub->get_score()}});
                task_json["submissions"] = submissions_json;

                tasks_json.push_back(task_json);
                current_task = current_task->get_next_task();
            }
            course_json["tasks"] = tasks_json;

            courses_json.push_back(course_json);
            current_course = current_course->get_next_cours();
        }
        student_json["courses"] = courses_json;

        j["students"].push_back(student_json);
        current_student = current_student->get_nextS();
    }
    ofstream file("student.json");
    file << j.dump(4);
    file.close();
}

void save_professors(Professor *head)
{
    json j;
    j["professors"] = json::array();

    Professor *current = head;
    while (current != nullptr)
    {
        json professor_json = {
            {"username", current->get_username()},
            {"password", current->get_password()},
            {"firstname", current->get_firstname()},
            {"lastname", current->get_lastname()},
            {"id", current->get_id()},
            {"isActive", current->get_isActiveP()}};

        // ذخیره درس‌های استاد
        json courses_json = json::array();
        Cours *course = current->get_teachingCourse();
        while (course != nullptr)
        {
            json course_json = {
                {"id", course->get_id()},
                {"name", course->get_Coursename()},
                {"college", course->get_College()},
                {"units", course->get_units()},
                {"capacity", course->get_capacity()},
                {"day", course->get_day()},
                {"time", course->get_time()},
                {"notice", course->get_Notice()}};

            // ذخیره دانشجویان این درس
            json students_json = json::array();
            Student *student = course->get_Students();
            while (student != nullptr)
            {
                students_json.push_back({{"id", student->get_id()},
                                         {"name", student->get_firstname() + " " + student->get_lastname()}});
                student = student->get_nextS();
            }
            course_json["students"] = students_json;

            // ذخیره تمرین‌های این درس
            json tasks_json = json::array();
            Task *task = course->get_Tasks();
            while (task != nullptr)
            {
                json task_json = {
                    {"name", task->get_nametask()},
                    {"description", task->get_description()},
                    {"deadline", task->get_deadline()}};

                // ذخیره پاسخ‌های این تمرین
                json submissions_json = json::array();
                Submission *sub = task->get_Submissions();
                submissions_json.push_back({{"student_id", sub->get_id()},
                                            {"answer", sub->get_answer()},
                                            {"score", sub->get_score()}});
                task_json["submissions"] = submissions_json;

                tasks_json.push_back(task_json);
                task = task->get_next_task();
            }
            course_json["tasks"] = tasks_json;

            courses_json.push_back(course_json);
            course = course->get_next_cours();
        }
        professor_json["courses"] = courses_json;

        j["professors"].push_back(professor_json);
        current = current->get_nextP();
    }
    ofstream file("professor.json");
    file << j.dump(4);
    file.close();
}

void save_courses(Cours *head)
{
    json j;
    j["courses"] = json::array();

    Cours *current = head;
    while (current != nullptr)
    {
        json course_json = {
            {"id", current->get_id()},
            {"name", current->get_Coursename()},
            {"college", current->get_College()},
            {"professor", {{"firstname", current->get_Professorname()}, {"lastname", current->get_Professorfamaly()}}},
            {"units", current->get_units()},
            {"capacity", current->get_capacity()},
            {"registered", current->get_registeredS()},
            {"score", current->get_score()},
            {"average", current->get_average_Scores()},
            {"day", current->get_day()},
            {"time", current->get_time()},
            {"notice", current->get_Notice()}};

        // ذخیره دانشجویان (فقط IDها)
        json students_json = json::array();
        Student *student = current->get_Students();
        while (student != nullptr) {
            students_json.push_back({
                {"id", student->get_id()},
                {"username", student->get_username()},
                {"password", student->get_password()},
                {"firstname", student->get_firstname()},
                {"lastname", student->get_lastname()},
                {"major", student->get_major()},
                {"isActive", student->get_isActiveS()}
                // سایر اطلاعات دانشجو
            });
            student = student->get_nextS();
        }
        course_json["students"] = students_json;

        // ذخیره تمرین‌ها
        json tasks_json = json::array();
        Task *task = current->get_Tasks();
        while (task != nullptr)
        {
            json task_json = {
                {"name", task->get_nametask()},
                {"description", task->get_description()},
                {"deadline", task->get_deadline()}};

            // ذخیره پاسخ‌ها
            json submissions_json = json::array();
            Submission *sub = task->get_Submissions();

            submissions_json.push_back({{"student_id", sub->get_id()},
                                        {"answer", sub->get_answer()},
                                        {"score", sub->get_score()}});
            task_json["submissions"] = submissions_json;

            tasks_json.push_back(task_json);
            task = task->get_next_task();
        }
        course_json["tasks"] = tasks_json;

        j["courses"].push_back(course_json);
        current = current->get_next_cours();
    }

    ofstream file("course.json");
    file << j.dump(4); // عدد 4 برای فرمت زیبا
    file.close();
}
