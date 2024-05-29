#pragma once
#include "global.hpp"

class Person;

class Course
{
public:
    Course(int cid, string name, int credit, int prerequisite, vector<int> majors_id);
    bool id_match(int id);
    bool unique_id_match(int id);
    bool is_in_this_major(int id);
    void set_information(Person* professor, int capacity, int class_number, Time time, Date exam_date, int unique_id);
    bool has_conflict(Course* course);
    bool prerequisite_met(string semester);
    Date get_exam_date();
    int get_id() {return unique_id;}
private:
    int cid;
    int unique_id;
    int unique_id_counter = 1;
    Person* professor = nullptr;
    int capacity;
    int class_number;
    string name;
    int credit;
    int prerequisite;
    vector<int> majors_id;
    Time time;
    Date exam_date;
};