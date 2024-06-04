#pragma once
#include "global.hpp"
#include "user.hpp"
#include "professor.hpp"

class Admin : public User
{
public:
    Admin(int id, string name, string password);
    void course_offering(shared_ptr<Professor> professor);
private:
    void print_inf();
};