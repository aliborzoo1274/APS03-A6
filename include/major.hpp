#pragma once
#include "global.hpp"

class Major
{
public:
    Major(int mid, string name);
    int get_id();
    string get_name();
private:
    int mid;
    string name;
};