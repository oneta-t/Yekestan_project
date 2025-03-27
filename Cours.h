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
    int registeredS;
    float Score;
    float Average_Scores;
    string Day;
    string Time;
    string Notice;
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
    void set_score(int score);
    float get_average_Scores();
    string get_Notice();
    void set_Notice(string notice);
    void Addstudent(Student*newstudent);
    void Addtask(Task*newtaske);
    Professor *get_Professor();
    Student *get_Students();
    Task *get_Tasks();
    Cours* get_next_cours();
    void set_next_cours(Cours* newcours);   
    void Calculate_average();
};

#endif;