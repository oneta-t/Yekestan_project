#ifndef TASK_H
#define TASK_H
#include "Student.h"
#include "Professor.h"
#include "Cours.h"
#include "Submission.h"

class Task
{
private:
    string Description;
    string Deadline;
    Submission *submission;
    Task * next_t;

public:
    Task(string description,string deadline);
    string get_description();
    string get_deadline();
    Task* get_next_t();
    void set_next_t(Task*nexttaske);
    Submission*get_Submissions();
    void Add_Submissions(Submission*newsub);
};

#endif