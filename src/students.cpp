#include "students.hpp"

Student::Student(int sid, string name, int major_id, int semester, string password)
{
    this->sid = sid;
    this->name = name;
    this->major_id = major_id;
    this->semester = semester;
    this->password = password;
}