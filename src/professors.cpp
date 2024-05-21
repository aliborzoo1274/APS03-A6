#include "professors.hpp"

Professor::Professor(int pid, string name, int major_id, string position, string password)
{
    this->pid = pid;
    this->name = name;
    this->major_id = major_id;
    this->position = position;
    this->password = password;
}