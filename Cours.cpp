#include "Cours.h"

Cours::Cours(string name, string college, int units, int capacity, float score, float average, string day, string time, Professor *prof)
{
    Coursename = name;
    College = college;
    Units = units;
    Capacity = capacity;
    Score = score;
    Average_Scores = average;
    Day = day;
    Time = time;
    professor = prof;
}

string Cours::get_Coursename()
{
    return Coursename;
}

string Cours::get_College()
{
    return College;
}

string Cours::get_day()
{
    return Day;
}

string Cours::get_time()
{
    return Time;
}

int Cours::get_units()
{
    return Units;
}

int Cours::get_capacity()
{
    return Capacity;
}

float Cours::get_score()
{
    return Score;
}

void Cours::set_score(int score)
{
    Score=score;
}

float Cours::get_average_Scores()
{
    return Average_Scores;
}

string Cours::get_Notice()
{
    return Notice;
}

void Cours::set_Notice(string notice)
{
    Notice=notice;
}

void Cours::Addstudent(Student *newstudent)
{
    students->set_nextS(newstudent);
    newstudent = students;
}

void Cours::Addtask(Task *newtaske)
{
    tasks->set_next_task(newtaske);
    newtaske = tasks;
}

Professor *Cours::get_Professor()
{
    return professor;
}

Student *Cours::get_Students()
{
    return students;
}

Task *Cours::get_Tasks()
{
    return tasks;
}

Cours *Cours::get_next_cours()
{
    return nextcours;
}

void Cours::set_next_cours(Cours *newcours)
{
    nextcours = newcours;
}
