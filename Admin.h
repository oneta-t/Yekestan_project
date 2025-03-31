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

#endif
// // برای ذخیره لیست دروس
// void saveCoursesToBinary(Cours* head, const string& filename) {
//     ofstream file(filename, ios::binary);
//     Cours* current = head;
//     while (current != nullptr) {
//         // ذخیره داده‌های پایه
//         string name = current->get_Coursename();
//         int nameLen = name.length();
//         file.write(reinterpret_cast<char*>(&nameLen), sizeof(int));
//         file.write(name.c_str(), nameLen);
        
//         // ذخیره سایر فیلدها به همین صورت...
//         current = current->get_next_cours();
//     }
//     file.close();
// }

// // برای بارگذاری
// Cours* loadCoursesFromBinary(const string& filename, Professor* profList) {
//     ifstream file(filename, ios::binary);
//     Cours* head = nullptr;
//     Cours* tail = nullptr;
    
//     while (file) {
//         // خواندن نام درس
//         int nameLen;
//         file.read(reinterpret_cast<char*>(&nameLen), sizeof(int));
//         char* buffer = new char[nameLen+1];
//         file.read(buffer, nameLen);
//         buffer[nameLen] = '\0';
//         string courseName(buffer);
//         delete[] buffer;
        
//         // خواندن سایر فیلدها...
        
//         // ایجاد شیء جدید
//         Cours* newCourse = new Cours(courseName, /* سایر پارامترها */);
//         if (!head) head = newCourse;
//         else tail->set_next_cours(newCourse);
//         tail = newCourse;
//     }
//     file.close();
//     return head;
// }
// #include <nlohmann/json.hpp>
// using json = nlohmann::json;

// // برای ذخیره
// void saveCoursesToJSON(Cours* head, const string& filename) {
//     json j;
//     Cours* current = head;
//     while (current != nullptr) {
//         json courseJson;
//         courseJson["name"] = current->get_Coursename();
//         courseJson["college"] = current->get_College();
//         // ... سایر فیلدها
        
//         j["courses"].push_back(courseJson);
//         current = current->get_next_cours();
//     }
    
//     ofstream file(filename);
//     file << j.dump(4); // عدد 4 برای فورمت زیبا
//     file.close();
// }

// // برای بارگذاری
// Cours* loadCoursesFromJSON(const string& filename, Professor* profList) {
//     ifstream file(filename);
//     json j;
//     file >> j;
    
//     Cours* head = nullptr;
//     Cours* tail = nullptr;
    
//     for (auto& courseJson : j["courses"]) {
//         Cours* newCourse = new Cours(
//             courseJson["name"].get<string>(),
//             courseJson["college"].get<string>(),
//             // ... سایر پارامترها
//         );
        
//         if (!head) head = newCourse;
//         else tail->set_next_cours(newCourse);
//         tail = newCourse;
//     }
    
//     return head;
// }