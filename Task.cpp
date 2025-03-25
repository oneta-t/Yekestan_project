#include "Task.h"

Task::Task(string description, string deadline)
{
    Deadline = deadline;
    Description = description;
    submission=nullptr;
    next_t = nullptr;
}

string Task::get_description()
{
    return Description;
}

string Task::get_deadline()
{
    return Deadline;
}

Task *Task::get_next_task()
{
    return next_t;
}

void Task::set_next_task(Task *nexttaske)
{
    next_t = nexttaske;
}

Submission *Task::get_Submissions()
{
    return submission;
}

// void Task::Add_Submissions(Submission*newsub)
// {
//     newsub->set_next_sub(submission);
//     submission=newsub;
// }