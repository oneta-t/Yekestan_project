#pragma once
#include "User.h"
#include "Cours.h"
#include"Professor.h"
#include "Task.h"
#include "Submission.h"
#include "save_load.h"
class Cours;

class Student : public User
{
private:
    string Firstname;
    string Lastname;
    string Major;
    Student *next_S;
    Cours* list_courses;
    int Id;
    bool isActiveS;

public:
    Student(string uname, string pwd, string name, string family, string major, int id);
    ~Student();
    const string get_firstname()const;
    const string get_lastname()const;
    const string get_major()const;
    int get_id()const;
    bool get_isActiveS()const;
    void set_isActiveS(bool x);
    Cours* get_list_courses();
    void set_list_courses(Cours*courses);
    Student *get_nextS();
    void set_nextS(Student *nextS);
    void Sign_in_S(Student *&headStudent,Cours*&courses);
    void Sign_up_S(Student *&headStudent);
    void Add_student(Student *&headStudent, Student *newstudent);
    void View_registered_courses();
    void view_Available_Courses(Cours* allcourses);
    void Course_registration(Cours *&allcourses,Student*&headStudent);
    void view_Task_Grades();
    void Answer_to_task(Student*&headStudent); 
    void student_page(Cours *&courses,Student*&headStudent);
    void Grading_course(Student*&headStudent);
    void view_notice();
};
