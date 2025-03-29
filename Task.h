#ifndef TASK_H
#define TASK_H
#include "Student.h"
#include "Professor.h"
#include "Cours.h"
#include "Submission.h"

class Task
{
private:
    string Name;
    string Description;
    string Deadline;
    Submission *submission;
    Task * next_t;

public:
    Task(string name,string description,string deadline);
    string get_nametask();
    string get_description();
    string get_deadline();
    Task* get_next_task();
    void set_next_task(Task*nexttaske);
    Submission*get_Submissions();
    void Add_Submissions(string studentname,int Id,string answer);
};

#endif