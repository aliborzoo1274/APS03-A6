#pragma once
#include "global.hpp"
#include "read_files.hpp"
#include "majors.hpp"
#include "students.hpp"
#include "courses.hpp"
#include "professors.hpp"

class System
{
public:
    System(vector<Major> majors, vector<Student> students, vector<Course> courses, vector<Professor> professors);
    void answer_command();
private:
    vector<Major> majors;
    vector<Student> students;
    vector<Course> courses;
    vector<Professor> professors;
    void get_method();
    void post_method();
    void put_method();
    void delete_method();
};