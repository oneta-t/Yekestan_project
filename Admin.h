#ifndef ADMIN_H
#define ADMIN_H
#include "User.h"
#include "Student.h"
#include "Professor.h"
#include "Cours.h"

class Admin
{
public:
    void view_all_students(Student *headStudent);
    void view_all_professors(Professor *headProfessor);
    void view_all_courses(Cours *headCourse);
    void create_student(Student*& headStudent);
    void create_professor(Professor*& headProfessor);
    void delete_student(Student* headStudent);
    void delete_professor(Professor* headProfessor);
    void restore_student(Student* headStudent);
    void restore_professor(Professor* headProfessor);
};

void Admin_page(Cours*headcourse,Student*headstd,Professor*headprof); 

#endif