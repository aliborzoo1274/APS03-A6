#pragma once
#include "global.hpp"
#include "system.hpp"
#include "majors.hpp"
#include "students.hpp"
#include "courses.hpp"
#include "professors.hpp"

class System;

System* read_files(char* argv[]);

vector<Major> read_majors_file(ifstream& majors);

vector<Student> read_students_file(ifstream& students);

vector<Course> read_courses_file(ifstream& courses);

vector<Professor> read_professors_file(ifstream& professors);