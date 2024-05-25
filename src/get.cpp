#include "system.hpp"

void System::get_method()
{
    for (int i = 0; i < persons.size(); i++)
    {
        persons[i].get_inf();
        persons[i].print_connected();
    }
    answer_command();
}