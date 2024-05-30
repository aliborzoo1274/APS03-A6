#include "person.hpp"
#include "course.hpp"

Person::Person(string type, int id, string name, int major_id, string major_name, string semester_or_position, string password)
{
    this->type = type;
    this->id = id;
    this->name = name;
    this->major_id = major_id;
    this->major_name = major_name;
    this->semester_or_position = semester_or_position;
    this->password = password;
}

Person::Person(string type, int id, string name, string password)
{
    this->type = type;
    this->id = id;
    this->name = name;
    this->password = password;
}

bool Person::id_match(int id)
{
    if (this->id == id)
        return true;
    else return false;
}

bool Person::password_match(string password)
{
    if (this->password == password)
        return true;
    else return false;
}

bool Person::is_admin()
{
    if (type == "admin")
        return true;
    else return false;
}

bool Person::is_student()
{
    if (type == "student")
        return true;
    else return false;
}

bool Person::is_professor()
{
    if (type == "professor")
        return true;
    else return false;
}

void Person::send_post(string title, string message)
{
    int post_id = num_of_posts;
    posts.push_back({post_id, title, message});
    num_of_posts++;
    send_notification(this->id, this->name, "New Post");
}

void Person::send_notification(int id, string name, string message)
{
    for (auto c : connected_users)
        c->notifications.push_back({id, name, message});
}

bool Person::has_post_id_then_delete(int id)
{
    for (int i = 0; i < posts.size(); i++)
    {
        if (posts[i].post_id == id)
        {
            posts.erase(posts.begin() + i);
            return true;
        }
    }
    return false;
}

bool Person::connected_before_to_you(int id)
{
    if (this->id != id)
    {
        for (int i = 0; i < connected_users.size(); i++)
        {
            if (connected_users[i]->id == id)
                return true;
        }
    }
    else return true;
    return false;
}

void Person::connect_to_person(Person* person)
{
    connected_users.push_back(person);
}

void Person::show_page()
{
    if (type == "admin")
        cout << ADMIN << endl;
    else
    {
        cout << name << ' ' << major_name << ' ' << semester_or_position;
        if (courses.size() != 0)
        {
            cout << ' ';
            for (int i = 0; i < courses.size() - 1; i++)
                cout << courses[i]->get_name() << ',';
            cout << courses[courses.size() - 1]->get_name() << endl;
        }
        else cout << endl;
        for (int i = posts.size() - 1; i >= 0; i--)
            cout << posts[i].post_id << ' ' << '"' << posts[i].title << '"' << endl;
    }
}

bool Person::has_post_then_show_it(int id)
{
    for (int i = 0; i < posts.size(); i++)
    {
        if (posts[i].post_id == id)
        {
            cout << name << ' ' << major_name << ' ' << semester_or_position << endl;
            cout << posts[i].post_id << ' ' << '"' << posts[i].title << '"' << ' ' << '"' << posts[i].message << '"' << endl;
            return true;
        }
    }
    return false;
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

void Person::course_offering(Person* professor)
{
    send_notification(professor->id, professor->name, "New Course Offering");
}

void Person::set_course(Course* course)
{
    courses.push_back(course);
}

bool Person::is_busy(Course* course)
{
    for (int i = 0; i < courses.size(); i++)
    {
        if (courses[i]->has_conflict(course))
            return true;
    }
    return false;
}

bool Person::has_exam_date_conflict(Date date)
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

bool Person::has_course_id_then_delete(int id)
{
    for (int i = 0; i < courses.size(); i++)
    {
        if (courses[i]->unique_id_match(id))
        {
            courses.erase(courses.begin() + i);
            send_notification(id, name, "Delete Course");
            return true;
        }
    }
    return false;
}

bool Person::show_courses()
{
    if (courses.size() == 0)
        return false;
    for (int i = 0; i < courses.size(); i++)
    {
        string p_name = courses[i]->get_professor()->name;
        courses[i]->print(p_name, "person");
    }
    return true;
}

void Person::get_course()
{
    send_notification(id, name, "Get Course");
}

int Person::get_major_id()
{
    return major_id;
}

string Person::get_name()
{
    return name;
}

string Person::get_semester_or_position()
{
    return semester_or_position;
}