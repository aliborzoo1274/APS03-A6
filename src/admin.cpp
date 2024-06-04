#include "admin.hpp"

Admin::Admin(int id, string name, string password) : User(id, name, password) {}

void Admin::print_inf()
{
    cout << name << endl;
}

void Admin::course_offering(shared_ptr<Professor> professor)
{
    send_notification(professor->get_id(), professor->get_name(), "New Course Offering");
}