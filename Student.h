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

public:
    Student(string uname, string pwd, string name, string family, string major, int id);
    string get_firstname();
    string get_lastname();
    string get_major();
    int get_id();
    Student *get_nextS();
    Cours* get_list_courses();
    void set_list_courses(Cours*courses);
    void set_nextS(Student *nextS);
    void Sign_in_S(Student *&headStudent);
    void Sign_up_S(Student *&headStudent);
    void Add_student(Student *&headStudent, Student *newstudent);
    void View_registered_courses();
    
};


#endif