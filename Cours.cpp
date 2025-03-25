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

string Cours::get_Coursename()
{
    return Coursename;
}

Cours *Cours::get_next_cours()
{
    return nextcours;
}

void Cours::set_next_cours(Cours *newcours)
{
    nextcours=newcours;
}
