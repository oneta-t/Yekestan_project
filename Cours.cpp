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
    registeredS = 0;
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
    Score = score;
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
    Notice = notice;
}

void Cours::Addstudent(Student *newstudent)
{
    if (Capacity < registeredS)
    {
        cerr << RED << "Course capacity is full! Cannot add more students" << RESET << endl;
        return;
    }
    students->set_nextS(newstudent);
    newstudent = students;
    registeredS++;
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

void Cours::Calculate_average()
{
    float sum;
    int count;
    Student *temp = students;
    if (temp == nullptr)
    {
        cerr << RED << "You are not any student for this course" << RESET << endl;
        return;
    }
    while (temp != nullptr)
    {
        Cours *tempcours = temp->get_list_courses();
        while (tempcours != nullptr)
        {
            if (Coursename == tempcours->get_Coursename())
            {
                sum += tempcours->get_score();
                ++count;
                temp = temp->get_nextS();
            }
            tempcours = tempcours->get_next_cours();
        }
        temp=temp->get_nextS();
    }
    if (count > 0)
    {
        Average_Scores = sum / count;
    }
}
