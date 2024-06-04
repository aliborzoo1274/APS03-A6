#pragma once
#include "global.hpp"
#include "person.hpp"
#include "course.hpp"

class Student : public Person
{
public:
    Student(int id, string name, int major_id, string major_name, int semester, string password);
    bool has_exam_date_conflict(Date date);
    bool has_course_id_then_delete(int id);
    int get_semester();
private:
    int semester;
    void print_spec();
};