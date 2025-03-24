#include "User.h"

User::User(string uname, string pwd)
{
    Username = uname;
    Password = pwd;
}

string User::get_username()
{
    return Username;
}

string User::get_password()
{
    return Password;
}


