#pragma once
#include "User.h"
#include "Student.h"
#include "Professor.h"
#include "Cours.h"

class Admin
{
public:
    void view_all_students(Student *headStudent);
    void view_all_professors(Professor *headProfessor);
    void view_all_courses(Cours *headCourse, Student *allSTD);
    void create_student(Student *&headStudent);
    void create_professor(Professor *&headProfessor);
    void delete_student(Student *headStudent);
    void delete_professor(Professor *headProfessor);
    void restore_student(Student *headStudent);
    void restore_professor(Professor *headProfessor);
    Student *find_student_by_id(Student *head, int id) const;
};
void Admin_page(Cours *headcourse, Student *headstd, Professor *headprof);
