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
    Person* current_user = nullptr;
    vector<string> read_line();
    void order_done();
    void error(string message);
    void get_method();
    void post_method();
    void put_method();
    void delete_method();
    void post_login();
    void post_post();
    void delete_post();
    void post_connect();
    bool connected_before(int id);
    bool has_person_id_then_connect(int id);
};