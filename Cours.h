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
public:
    Cours(string name,string college,int units,int capacity,float score,float average,string day,string time,Professor*prof);
    void Addstudent(Student*newstudent);
    void Addtask(Task*newtaske);
    Professor *get_Professor();
    Student *get_Students();
    Task *get_Tasks();
    string get_Coursename();
};

#endif;