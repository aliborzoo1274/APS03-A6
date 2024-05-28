#include "person.hpp"

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

void Person::send_post(string title, string message)
{
    int post_id = num_of_posts;
    posts.push_back({post_id, title, message});
    num_of_posts++;
    for (auto c : connected_users)
        c->notifications.push_back({this->id, this->name, "New Post"});
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
    if (type == "student")
        cout << name << ' ' << major_name << ' ' << semester_or_position << endl;
    else if (type == "professor")
        cout << name << ' ' << semester_or_position << endl;
    for (int i = posts.size() - 1; i >= 0; i--)
        cout << posts[i].post_id << ' ' << '"' << posts[i].title << '"' << endl;
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