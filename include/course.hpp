#pragma once
#include "global.hpp"

class Course
{
public:
    Course(int cid, string name, int credit, int prerequisite, vector<int> majors_id);
private:
    int cid;
    string name;
    int credit;
    int prerequisite;
    vector<int> majors_id;
};