#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <limits>
#include <memory>
using namespace std;

const int TRUE = 1;
const char FIRST_DELIM = ',';
const char SECOND_DELIM = ';';
const string ADMIN = "u";

struct Time
{
    string week_day;
    float start_time;
    float end_time;
};

struct Date
{
    int year;
    int month;
    int day;
};