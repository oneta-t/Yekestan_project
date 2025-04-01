#ifndef SUBMISSION_H
#define SUBMISSION_H
#include "Student.h"
#include "Professor.h"
#include "Cours.h"

class Submission
{
private:
    string student_name;
    int Id;
    string Answer;
    float Score;
    //Submission *Next_sub;

public:
    Submission(int id,string name,string answer,float score);
    string get_student_name();
    int get_id();
    string get_answer();
    float get_score();
    void set_score(float scour);
    void set_student_name(string name);
    // Submission* get_next_sub();
    // void Submission::set_next_sub(Submission*next_submission);
};

#endif