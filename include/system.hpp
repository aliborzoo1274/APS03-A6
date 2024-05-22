#pragma once
#include "global.hpp"
#include "read_files.hpp"
#include "major.hpp"
#include "course.hpp"
#include "person.hpp"

class System
{
public:
    System(vector<Major> majors, vector<Person> persons, vector<Course> courses);
    void answer_command();
private:
    vector<Major> majors;
    vector<Person> persons;
    vector<Course> courses;
    void get_method();
    void post_method();
    void put_method();
    void delete_method();
    void post_login();
};