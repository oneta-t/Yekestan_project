#ifndef STUDENT_H
#define STUDENT_H
#include "User.h"
#include "Cours.h"

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
    string get_firstname();
    string get_lastname();
    string get_major();
    int get_id();
    bool get_isActiveS();
    void set_isActiveS(bool x);
    Cours* get_list_courses();
    void set_list_courses(Cours*courses);
    Student *get_nextS();
    void set_nextS(Student *nextS);
    void Sign_in_S(Student *&headStudent,Cours*courses);
    void Sign_up_S(Student *&headStudent);
    void Add_student(Student *&headStudent, Student *newstudent);
    void View_registered_courses();
    void view_Available_Courses(Cours* allcourses);
    void Course_registration(Cours *allcourses);
    void view_Task_Grades();
    void Answer_to_task(); 
    void student_page(Cours *courses, Student *student);
    void Grading_course();
    void view_notice();
};

#endif