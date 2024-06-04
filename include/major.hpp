#pragma once
#include "global.hpp"

class Major
{
public:
    Major(int mid, string name);
    bool match_id(int id);
    string get_name();
private:
    int mid;
    string name;
};