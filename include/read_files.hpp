#pragma once
#include "global.hpp"
#include "system.hpp"
#include "major.hpp"
#include "course.hpp"
#include "person.hpp"
#include "student.hpp"
#include "professor.hpp"

class System;

shared_ptr<System> read_files(char* argv[]);

vector<Major> read_majors_file(ifstream& majors);

vector<Student> read_students_file(ifstream& students, vector<Major> majors_list);

vector<Course> read_courses_file(ifstream& courses);

vector<Professor> read_professors_file(ifstream& professors, vector<Major> majors_list);

vector<shared_ptr<Person>> adjustment_persons(vector<Student> students_list, vector<Professor> professors_list);