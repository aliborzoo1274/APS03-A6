#include "professor.hpp"

Professor::Professor(int id, string name, int major_id, string major_name, string position, string password) :
Person(id, name, major_id, major_name, password)
{
    this->position = position;
}

void Professor::print_spec()
{
    cout << name << ' ' << major_name << ' ' << position;
}

string Professor::get_position()
{
    return position;
}