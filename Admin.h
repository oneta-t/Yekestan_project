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
};

#endif
