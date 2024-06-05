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

void Student::take_course(shared_ptr<Course> course)
{
    courses.push_back(course);
    send_notification(id, name, "Get Course");
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

bool Student::allowed_then_course_post(int course_id, string title, string message, string image_address)
{
    for (int i = 0; i < courses.size(); i++)
    {
        if (courses[i]->unique_id_match(course_id))
        {
            if (courses[i]->is_ta(this))
            {
                courses[i]->send_course_post(this, title, message, image_address);
                return true;
            }
        }
    }
    return false;
}

int Student::get_semester()
{
    return semester;
}