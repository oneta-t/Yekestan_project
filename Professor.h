#ifndef PROFESSOR_H
#define PROFESSOR_H
#include "User.h"

class Professor : public User
{
private:
    string Firstname;
    string Lastname;
    int Id;
    Professor *next_P;
    // شاید یه چیزی برای اطلاعیه مثلا در نظر بگیریم
public:
    Professor(string uname, string pwd, string name, string family, int id);
    string get_firstname();
    string get_lastname();
    int get_id();
    Professor *get_nextP();
    void set_nextP(Professor *nextP);
    void Sign_in(Professor *&headProfessor);
    void Sign_up_P(Professor *&headProfessor);
    void Add_professor(Professor *&headProfessor, Professor *newprofessor);
};

#endif