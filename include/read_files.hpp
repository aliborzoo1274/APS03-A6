#pragma once
#include "global.hpp"
#include "system.hpp"
#include "major.hpp"
#include "course.hpp"
#include "person.hpp"

class System;

class Person;

System* read_files(char* argv[]);

vector<Major> read_majors_file(ifstream& majors);

vector<Person> read_person_file(ifstream& persons, vector<Major> majors_list, string type);

vector<Course> read_courses_file(ifstream& courses);

vector<Person> adjustment_persons(vector<Person> students_list, vector<Person> professors_list);