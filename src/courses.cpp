#include "courses.hpp"

Course::Course(int cid, string name, int credit, int prerequisite, vector<int> majors_id)
{
    this->cid = cid;
    this->name = name;
    this->credit = credit;
    this->prerequisite = prerequisite;
    this->majors_id = majors_id;
}