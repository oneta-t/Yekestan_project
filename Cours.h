#ifndef COURS_H
#define COURS.H
#include "Student.h"
#include "Professor.h"
#include "Task.h"

class Cours
{
private:
    string Coursename;
    string College;
    int Units;    
    int Capacity;
    float Score;
    float Average_Scores;
    string Day;
    string Time;
    Professor*professor;
    Student*students;
    Task* tasks;
    Cours *nextcours;
public:
    Cours(string name,string college,int units,int capacity,float score,float average,string day,string time,Professor*prof);
    string get_Coursename();
    string get_College();
    string get_day();
    string get_time();
    int get_units();
    int get_capacity();
    float get_score();
    float get_average_Scores();
    void Addstudent(Student*newstudent);
    void Addtask(Task*newtaske);
    Professor *get_Professor();
    Student *get_Students();
    Task *get_Tasks();
    Cours* get_next_cours();
    void set_next_cours(Cours* newcours);
};

#endif;