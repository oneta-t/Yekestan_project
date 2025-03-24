#include "Submission.h"

Submission::Submission(string name,string answer,float score)
{
    student_name=name;
    Answer=answer;
    Score=score;
    Next_sub=nullptr;
}

string Submission::get_student_name()
{
    return student_name;
}

string Submission::get_answer()
{
    return Answer;
}

float Submission::get_score()
{
    return Score;
}

Submission* Submission::get_next_sub()
{
    return Next_sub;
}

void Submission::set_next_sub(Submission*next_submission)
{
    Next_sub=next_submission;
}