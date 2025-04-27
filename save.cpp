#include "save.h"

void save_students(Student *head)
{
    json j;
    j["students"] = json::array();

    Student *current = head;
    while (current != nullptr)
    {
        json student_json = {
            {"username", current->get_username()},
            {"password", current->get_password()},
            {"firstname", current->get_firstname()},
            {"lastname", current->get_lastname()},
            {"major", current->get_major()},
            {"id", current->get_id()},
            {"isActive", current->get_isActiveS()}};

        // ذخیره اطلاعات کامل دروس دانشجو
        json courses_json = json::array();
        Cours *current_course = current->get_list_courses();
        while (current_course != nullptr)
        {
            json course_json = {
                {"id", current_course->get_id()},
                {"name", current_course->get_Coursename()},
                {"college", current_course->get_College()},
                {"professor", {{"firstname", current_course->get_Professorname()}, {"lastname", current_course->get_Professorfamaly()}}},
                {"units", current_course->get_units()},
                {"capacity", current_course->get_capacity()},
                {"registered", current_course->get_registeredS()},
                {"score", current_course->get_score()},
                {"average", current_course->get_average_Scores()},
                {"day", current_course->get_day()},
                {"time", current_course->get_time()},
                {"notices", current_course->get_Notice()}};

            // ذخیره تکالیف هر درس
            json tasks_json = json::array();
            Task *current_task = current_course->get_Tasks();
            while (current_task != nullptr)
            {
                json task_json = {
                    {"name", current_task->get_nametask()},
                    {"description", current_task->get_description()},
                    {"deadline", current_task->get_deadline()}};

                // ذخیره ارسال‌های هر تکلیف
                json submissions_json = json::array();
                Submission *current_sub = current_task->get_Submissions();
                while (current_sub != nullptr)
                {
                    submissions_json.push_back({{"student_id", current_sub->get_id()},
                                                {"answer", current_sub->get_answer()},
                                                {"score", current_sub->get_score()}});
                    current_sub = current_sub->get_next_sub();
                }
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
        current = current->get_nextS();
    }

    ofstream file("students.json");
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

        // ذخیره اطلاعات کامل دروس استاد
        json courses_json = json::array();
        Cours *current_course = current->get_teachingCourse();
        while (current_course != nullptr)
        {
            json course_json = {
                {"id", current_course->get_id()},
                {"name", current_course->get_Coursename()},
                {"college", current_course->get_College()},
                {"units", current_course->get_units()},
                {"capacity", current_course->get_capacity()},
                {"registered", current_course->get_registeredS()},
                {"score", current_course->get_score()},
                {"average", current_course->get_average_Scores()},
                {"day", current_course->get_day()},
                {"time", current_course->get_time()},
                {"notices", current_course->get_Notice()},
                {"studentRatings", current_course->getAllRatings()}};

            // ذخیره دانشجویان هر درس
            json students_json = json::array();
            const vector<int> &studentIds = current_course->get_stdID();
            for (int studentId : studentIds)
            {
                students_json.push_back({
                    {"id", studentId}
                    // می‌توانید اطلاعات کامل دانشجو را هم اینجا ذخیره کنید
                });
            }
            course_json["students"] = students_json;

            // ذخیره تکالیف هر درس
            json tasks_json = json::array();
            Task *current_task = current_course->get_Tasks();
            while (current_task != nullptr)
            {
                json task_json = {
                    {"name", current_task->get_nametask()},
                    {"description", current_task->get_description()},
                    {"deadline", current_task->get_deadline()}};

                // ذخیره ارسال‌های هر تکلیف
                json submissions_json = json::array();
                Submission *current_sub = current_task->get_Submissions();
                while (current_sub != nullptr)
                {
                    submissions_json.push_back({{"student_id", current_sub->get_id()},
                                                {"student_name", current_sub->get_student_name()},
                                                {"answer", current_sub->get_answer()},
                                                {"score", current_sub->get_score()}});
                    current_sub = current_sub->get_next_sub();
                }
                task_json["submissions"] = submissions_json;

                tasks_json.push_back(task_json);
                current_task = current_task->get_next_task();
            }
            course_json["tasks"] = tasks_json;

            courses_json.push_back(course_json);
            current_course = current_course->get_next_cours();
        }
        professor_json["courses"] = courses_json;

        j["professors"].push_back(professor_json);
        current = current->get_nextP();
    }

    ofstream file("professors.json");
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
            {"time", current->get_time()}};

        // ذخیره اطلاعیه‌ها
        json notices_json = json::array();
        for (const auto &notice : current->get_Notice())
        {
            notices_json.push_back(notice);
        }
        course_json["notices"] = notices_json;

        // ذخیره نمره‌های دانشجویان
        course_json["studentRatings"] = current->getAllRatings();

        // ذخیره دانشجویان (فقط IDها)
        json students_json = json::array();
        for (int student_id : current->get_stdID())
        {
            students_json.push_back(student_id);
        }
        course_json["students"] = students_json;

        // ذخیره تکالیف
        json tasks_json = json::array();
        Task *current_task = current->get_Tasks();
        while (current_task != nullptr)
        {
            json task_json = {
                {"name", current_task->get_nametask()},
                {"description", current_task->get_description()},
                {"deadline", current_task->get_deadline()}};

            // ذخیره ارسال‌ها
            json submissions_json = json::array();
            Submission *current_sub = current_task->get_Submissions();
            while (current_sub != nullptr)
            {
                submissions_json.push_back({{"student_id", current_sub->get_id()},
                                            {"student_name", current_sub->get_student_name()},
                                            {"answer", current_sub->get_answer()},
                                            {"score", current_sub->get_score()}});
                current_sub = current_sub->get_next_sub();
            }
            task_json["submissions"] = submissions_json;

            tasks_json.push_back(task_json);
            current_task = current_task->get_next_task();
        }
        course_json["tasks"] = tasks_json;

        j["courses"].push_back(course_json);
        current = current->get_next_cours();
    }

    ofstream file("courses.json");
    file << j.dump(4);
    file.close();
}