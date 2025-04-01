#ifndef LOAD_H
#define LOAD_H
#include "json.hpp"
#include "Student.h"
#include "Professor.h"
#include "Cours.h"
using json = nlohmann::json;

Student* load_students_with_courses();
Professor* load_professors(Student* all_students);
Cours* load_courses(Student* all_students);

#endif