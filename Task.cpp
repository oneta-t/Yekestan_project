#include "Task.h"

Task::Task(string description, string deadline)
{
    Deadline = deadline;
    Description = description;
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

Task *Task::get_next_t()
{
    return next_t;
}

void Task::set_next_t(Task *nexttaske)
{
    next_t = nexttaske;
}

Submission *Task::get_Submissions()
{
    return submission;
}

void Task::Add_Submissions(Submission*newsub)
{
    newsub->set_next_sub(submission);
    submission=newsub;
}