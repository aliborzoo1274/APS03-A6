#pragma once
#include "global.hpp"
#include "person.hpp"
#include "course.hpp"

class Student : public Person
{
public:
    Student(int id, string name, int major_id, string major_name, int semester, string password);
    bool has_exam_date_conflict(Date date);
    void take_course(shared_ptr<Course> course);
    bool has_course_id_then_delete(int course_id);
    bool allowed_then_course_post(int course_id, string title, string message, string image_address);
    int get_semester();
private:
    int semester;
    void print_spec();
};