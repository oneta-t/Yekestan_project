#pragma once
#include "User.h"
#include "Cours.h"
#include "Student.h"
#include "Task.h"
#include "Submission.h"
#include "save_load.h"
class Cours;
class Student;

class Professor : public User
{
private:
    string Firstname;
    string Lastname;
    int Id;
    Professor *next_P;
    Cours *teachingCourse;
    bool isActiveP;

public:
    Professor(string uname, string pwd, string name, string family, int id);
    ~Professor();
    string get_firstname();
    string get_lastname();
    int get_id();
    bool get_isActiveP();
    void set_isActiveP(bool x);
    Professor *get_nextP();
    void set_nextP(Professor *nextP);
    void Sign_in_P(Professor *&headProfessor, Cours *&courses, Student *&all_student);
    void Sign_up_P(Professor *&headProfessor);
    void Add_professor(Professor *&headProfessor, Professor *newprofessor);
    void create_cours(Cours *&headCourses, Professor *&headProfessor, Student *&allS, string name, string profname, string profamily, string college, int units, int capacity, string day, string time);
    void display_students(Cours *cours, Student *allStd);
    void create_task(Cours *&headcours, Cours *cours, string nametaske, string description, string deadline);
    void score_task(Student *&all_student);
    void score_student(Student *&all_student);
    void Add_notification(Professor *&headprof, Cours *&headcours);
    Cours *get_teachingCourse();
    void set_teachingCourse(Cours *courses);
    void professor_page(Cours *&courses, Student *&all_student, Professor *&headProfessor);
    void view_courses();
};
