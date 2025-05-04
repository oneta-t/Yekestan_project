#pragma once
#include "User.h"
#include "Student.h"
#include "Professor.h"
#include "Task.h"
#include "Submission.h"
#include "save_load.h"
#include <map>
class Task;

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
    map<int, float> studentRatings;
    string Day;
    string Time;
    vector<string> notices;
    vector<int> studentIds;
    Task *tasks;
    Cours *nextcours;

public:
    Cours(Student *all, string name, string college, string prof, string profamily, int units, int capacity, string day, string time);
    ~Cours();
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
    void set_score(float score);
    float get_average_Scores();
    void set_average_Scores(float avrege_score);
    void add_Notice(string content);
    const vector<string> &get_Notice();
    void Addstudent(int Id);
    void Addtask(Task *newtaske);
    const vector<int> &get_stdID();
    Task *get_Tasks();
    Cours *get_next_cours();
    void set_next_cours(Cours *newcours);
    void Calculate_average(Student *&allSTD);
    void set_std_give_scour(int studentId, float rating);
    void add_Student_rating(int studentId, float rating);
    float get_student_rating(int studentId) const;
    const map<int, float> &getAllRatings() const;
    void set_StudentIds(const vector<int> &newstd);
    Cours(const Cours &other);
};
