#pragma once
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[36m"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class User
{
protected:
    string Username;
    string Password;

public:
    User(string uname, string pwd);
    string get_username();
    string get_password();
};
