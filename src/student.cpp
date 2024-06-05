#include "student.hpp"

Student::Student(int id, string name, int major_id, string major_name, int semester, string password) :
Person(id, name, major_id, major_name, password)
{
    this->semester = semester;
}

void Student::print_spec()
{
    cout << name << ' ' << major_name << ' ' << semester;
}

bool Student::has_exam_date_conflict(Date date)
{
    for (int i = 0; i < courses.size(); i++)
    {
        if (courses[i]->get_exam_date().year == date.year &&
            courses[i]->get_exam_date().month == date.month &&
            courses[i]->get_exam_date().day == date.day)
            return true;
    }
    return false;
}

bool Student::has_course_id_then_delete(int course_id)
{
    for (int i = 0; i < courses.size(); i++)
    {
        if (courses[i]->unique_id_match(course_id))
        {
            courses.erase(courses.begin() + i);
            send_notification(id, name, "Delete Course");
            return true;
        }
    }
    return false;
}

int Student::get_semester()
{
    return semester;
}