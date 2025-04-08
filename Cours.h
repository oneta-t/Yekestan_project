#ifndef COURS_H
#define COURS .H
#include "Student.h"
#include "Professor.h"
#include "Task.h"

class Cours
{
private:
    int ID;
    static int nextId;
    string Coursename;
    string College;
    string professorname;
    string professorfamaiy;
    int Units;
    int Capacity;
    int registeredS;
    float Score;
    float Average_Scores;
    float std_give_scour;
    string Day;
    string Time;
    vector<string> notices;
    // string Notice;
    // Professor*professor;
    //Student *students;
    vector<int> studentIds;
    Task *tasks;
    Cours *nextcours;

public:
    // Cours(string name,string college,int units,int capacity,float score,float average,string day,string time,Professor*prof);
    Cours(Student*all,string name, string college, string prof, string profamily, int units, int capacity, string day, string time);
    int get_id();
    void set_id(int id);
    string get_Coursename();
    string get_Professorname();
    string get_Professorfamaly();
    string get_College();
    string get_day();
    string get_time();
    int get_units();
    int get_capacity();
    int get_registeredS();
    void set_registeredS(int regist);
    float get_score();
    void set_score(int score);
    float get_average_Scores();
    void add_Notice(string content);
    const vector<string>& get_Notice();
    //void show_notices();
    //void Addstudent(Student *newstudent);
    void Addstudent(int Id);
    void Addtask(Task *newtaske);
    // Professor *get_Professor();
    //Student *get_Students();
    const vector<int>& get_stdID();
    Task *get_Tasks();
    Cours *get_next_cours();
    void set_next_cours(Cours *newcours);
    void Calculate_average(Student*allSTD);
    float get_std_give_scour();
    void set_std_give_scour(int grad);
};

#endif;