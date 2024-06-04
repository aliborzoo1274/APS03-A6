#include "person.hpp"
#include "course.hpp"

Person::Person(int id, string name, int major_id, string major_name, string password) :
User(id , name, password)
{
    this->major_id = major_id;
    this->major_name = major_name;
}

void Person::print_inf()
{
    print_spec();
    print_courses();
}

void Person::print_courses()
{
    if (courses.size() != 0)
    {
        cout << ' ';
        for (int i = 0; i < courses.size() - 1; i++)
            cout << courses[i]->get_name() << ',';
        cout << courses[courses.size() - 1]->get_name() << endl;
    }
    else
        cout << endl;
}

void Person::set_notification(int id, string name, string message)
{
    notifications.push_back({id, name, message});
}

bool Person::show_notifications()
{
    if (notifications.size() == 0)
        return false;
    else
    {
        for (int i = notifications.size() - 1; i >= 0; i--)
            cout << notifications[i].person_id << ' ' << notifications[i].person_name << ": " << notifications[i].message << endl;
        vector<Notification>().swap(notifications);
        return true;
    }
}

bool Person::has_time_conflict(shared_ptr<Course> course)
{
    for (int i = 0; i < courses.size(); i++)
    {
        if (courses[i]->has_conflict(course))
            return true;
    }
    return false;
}

void Person::take_course(shared_ptr<Course> course)
{
    courses.push_back(course);
    send_notification(id, name, "Get Course");
}

bool Person::show_courses()
{
    if (courses.size() == 0)
        return false;
    for (auto course : courses)
        course->print("person");
    return true;
}

bool Person::allowed_then_course_post(int course_id, string title, string message, string image_address)
{
    for (int i = 0; i < courses.size(); i++)
    {
        if (courses[i]->id_match(course_id))
        {
            courses[i]->send_course_post(this, title, message, image_address);
            return true;
        }
    }
    return false;
}

bool Person::allowed_then_show_channel(int course_id)
{
    for (int i = 0; i < courses.size(); i++)
    {
        if (courses[i]->id_match(course_id))
        {
            courses[i]->show_posts();
            return true;
        }
    }
    return false;
}

int Person::get_id()
{
    return id;
}

string Person::get_name()
{
    return name;
}

int Person::get_major_id()
{
    return major_id;
}