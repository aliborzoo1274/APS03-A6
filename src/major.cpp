#include "major.hpp"

Major::Major(int mid, string name)
{
    this->mid = mid;
    this->name = name;
}

int Major::get_id()
{
    return mid;
}

string Major::get_name()
{
    return name;
}