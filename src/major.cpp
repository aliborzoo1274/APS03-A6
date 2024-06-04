#include "major.hpp"

Major::Major(int mid, string name)
{
    this->mid = mid;
    this->name = name;
}

bool Major::match_id(int id)
{
    if (mid == id)
        return true;
    return false;
}

string Major::get_name()
{
    return name;
}