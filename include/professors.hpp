#pragma once
#include "global.hpp"

class Professor
{
public:
    Professor(int pid, string name, int major_id, string position, string password);
private:
    int pid;
    string name;
    int major_id;
    string position;
    string password;
};