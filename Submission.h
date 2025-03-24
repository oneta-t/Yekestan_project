#ifndef SUBMISSION_H
#define SUBMISSION_H
#include "Student.h"
#include "Professor.h"
#include "Cours.h"

class Submission
{
private:
    string student_name;
    string Answer;
    float Score;
    Submission *Next_sub;

public:
    Submission(string name,string answer,float score);
    string get_student_name();
    string get_answer();
    float get_score();
    Submission* get_next_sub();
    void Submission::set_next_sub(Submission*next_submission);
};

#endif