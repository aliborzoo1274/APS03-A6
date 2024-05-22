#pragma once
#include "global.hpp"

class Person
{
public:
    Person(string type, int id, string name, int major_id, string semester_or_position, string password);
private:
    string type;
    int id;
    string name;
    int major_id;
    string semester_or_position;
    string password;
};