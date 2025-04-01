#ifndef SAVE_H
#define SAVE_H
#include "json.hpp"
#include "Student.h"
#include "Professor.h"
#include "Cours.h"
#include "Task.h"
#include "Submission.h"
using json = nlohmann::json;

void save_students(Student* head);
void save_professors(Professor* head);
void save_courses(Cours *head);

#endif