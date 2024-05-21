#include "system.hpp"

System::System(vector<Major> majors, vector<Student> students, vector<Course> courses, vector<Professor> professors)
{
    this->majors = majors;
    this->students = students;
    this->courses = courses;
    this->professors = professors;
}

void System::answer_command()
{
    string command_method;
    cin >> command_method;
    if (command_method == "GET")
        get_method();
    else if (command_method == "POST")
        post_method();
    else if (command_method == "PUT")
        put_method();
    else if (command_method == "DELETE")
        delete_method();
}

void System::get_method() {}

void System::post_method() {}

void System::put_method() {}

void System::delete_method() {}