#pragma once
#include "global.hpp"
#include "person.hpp"

class Professor : public Person
{
public:
    Professor(int id, string name, int major_id, string major_name, string position, string password);
    string get_position();
private:
    string position;
    void print_spec();
};