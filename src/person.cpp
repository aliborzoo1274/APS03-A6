#include "person.hpp"

Person::Person(string type, int id, string name, int major_id, string semester_or_position, string password)
{
    this->type = type;
    this->id = id;
    this->name = name;
    this->major_id = major_id;
    this->semester_or_position = semester_or_position;
    this->password = password;
}