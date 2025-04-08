#include "Cours.h"
#include <vector>

int Cours::nextId = 0;
// Cours::Cours(string name, string college, int units, int capacity, float score, float average, string day, string time, Professor *prof)
Cours::Cours(Student*all,string name, string college, string profname, string profamily, int units, int capacity, string day, string time)
{
    Coursename = name;
    College = college;
    Units = units;
    Capacity = capacity;
    Score = 0;
    this->Calculate_average(all);
    Day = day;
    Time = time;
    professorname = profname;
    professorfamaiy = profamily;
    registeredS = 0;
    std_give_scour = 0;
    ID = ++nextId;
}

int Cours::get_id()
{
    return ID;
}

void Cours::set_id(int id)
{
    ID = id;
}

string Cours::get_Coursename()
{
    return Coursename;
}

string Cours::get_Professorname()
{
    return professorname;
}

string Cours::get_Professorfamaly()
{
    return professorfamaiy;
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

int Cours::get_registeredS()
{
    return registeredS;
}

void Cours::set_registeredS(int regist)
{
    registeredS = regist;
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

void Cours::add_Notice(string content)
{
    notices.push_back(content);
}

// void Cours::show_notices()
// {
//     cout <<"\033[1:34m"<< "Course announcements: " <<RESET<< endl;
//     for (int i = 0; i < notices.size(); ++i)
//     {
//         cout <<BLUE<< i + 1 << ")" << notices[i] << endl;
//         cout<<endl;
//         cout<< "-------------------" <<RESET<< endl;
//     }
// }

const vector<string> &Cours::get_Notice()
{
    return notices;
}

// void Cours::Addstudent(Student *newstudent)
// {
//     if (Capacity < registeredS)
//     {
//         cerr << RED << "Course capacity is full! Cannot add more students" << RESET << endl;
//         return;
//     }
//     students->set_nextS(newstudent);
//     newstudent = students;
//     registeredS++;
// }

void Cours::Addtask(Task *newtaske)
{
    tasks->set_next_task(newtaske);
    newtaske = tasks;
}

// Professor *Cours::get_Professor()
// {
//     return professor;
// }

// Student *Cours::get_Students()
// {
//     return students;
// }

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

void Cours::Calculate_average(Student *allSTD)
{
    float sum;
    int count;
    Student *temp = allSTD;
    if (temp == nullptr)
    {
        cerr << RED << "The list of students is empty." << RESET << endl;
        return;
    }
    if (studentIds.empty() == 0)
    {
        cerr << RED << "You are not any student for this course" << RESET << endl;
        return;
    }
    while (temp != nullptr)
    {
        for (int i = 0; i < count; i++)
        {
            if (temp->get_id() == studentIds[i])
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
            }
        }
        temp = temp->get_nextS();
    }
    if (count > 0)
    {
        Average_Scores = sum / count;
    }
}

float Cours::get_std_give_scour()
{
    return std_give_scour;
}

void Cours::set_std_give_scour(int grad)
{
    std_give_scour = grad;
}

const vector<int> &Cours::get_stdID()
{
    return studentIds;
}

void Cours::Addstudent(int Id)
{
    if (Capacity < registeredS)
    {
        cerr << RED << "Course capacity is full! Cannot add more students" << RESET << endl;
        return;
    }
    studentIds.push_back(Id);
    registeredS++;
}
