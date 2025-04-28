#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include "Student.h"
#include "Professor.h"
#include "Cours.h"

using namespace std;
class Student;
class Professor;
class Cours;

void save_students(Student* headStudent);
Student* load_students();
void save_professors(Professor* headProfessor);
Professor* load_professors(Student* all_students);
void save_courses(Cours* headCourse);
Cours* load_courses(Student* allStudents);

