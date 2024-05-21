#pragma once
#include "global.hpp"

class Student
{
public:
    Student(int sid, string name, int major_id, int semester, string password);
private:
    int sid;
    string name;
    int major_id;
    int semester;
    string password;
};