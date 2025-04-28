#include "Task.h"

Task::Task(string name,string description, string deadline)
{
    Name=name;
    Deadline = deadline;
    Description = description;
    submission=nullptr;
    next_t = nullptr;
}

Task::~Task() {
    Submission* tempSub = submission;
    while (tempSub != nullptr) {
        Submission* nextSub = tempSub->get_next_sub();
        delete tempSub;
        tempSub = nextSub;
    }
}


string Task::get_nametask()
{
    return Name;
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

void Task::Add_Submissions(string studentname, int id, string answer)
{
    if (submission == nullptr) {
        submission = new Submission(id, studentname, answer, 0.0);
    } else {
        Submission* temp = submission;
        while (temp->get_next_sub() != nullptr) {
            temp = temp->get_next_sub();
        }
        temp->set_next_sub(new Submission(id, studentname, answer, 0.0));
    }
}