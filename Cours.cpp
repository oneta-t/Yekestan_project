#include "Cours.h"
#include <vector>

int Cours::nextId = 0;
Cours::Cours(Student *all, string name, string college, string profname, string profamily, int units, int capacity, string day, string time)
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
    ID = ++nextId;
}

Cours::~Cours()
{
    Task *tempTask = tasks;
    while (tempTask != nullptr)
    {
        Task *nextTask = tempTask->get_next_task();
        delete tempTask;
        tempTask = nextTask;
    }
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

void Cours::set_score(float score)
{
    Score = score;
}

float Cours::get_average_Scores()
{
    return Average_Scores;
}

void Cours::set_average_Scores(float avrege_score)
{
    Average_Scores = avrege_score;
}

void Cours::add_Notice(string content)
{
    notices.push_back(content);
}

const vector<string> &Cours::get_Notice()
{
    return notices;
}

void Cours::Addtask(Task *newtaske)
{
    tasks->set_next_task(newtaske);
    newtaske = tasks;
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

void Cours::Calculate_average(Student *allSTD)
{
    float sum;
    float count = 0;
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
        for (size_t i = 0; i < studentIds.size(); i++)
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

void Cours::set_std_give_scour(int studentId, float rating)
{
    if (rating < 0.0f || rating > 20.0f)
    {
        cerr << RED << "Rating must be between 0.0 and 20.0" << RESET << endl;
        return;
    }
    studentRatings[studentId] = rating;
}

void Cours::add_Student_rating(int studentId, float rating)
{
    if (rating >= 0.0f && rating <= 20.0f)
    {
        studentRatings[studentId] = rating;
    }
}

float Cours::get_student_rating(int studentId) const
{
    auto it = studentRatings.find(studentId);

    if (it != studentRatings.end())
    {
        return it->second;
    }
    else
    {
        return -1.0f;
    }
}

const map<int, float> &Cours::getAllRatings() const
{
    return studentRatings;
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

void Cours::set_StudentIds(const vector<int> &newstd)
{
    studentIds = newstd;
}
