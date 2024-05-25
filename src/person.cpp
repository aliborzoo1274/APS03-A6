#include "person.hpp"

Person::Person(string type, int id, string name, int major_id, string semester_or_position, string password)
{
    this->type = type;
    this->id = id;
    this->name = name;
    this->major_id = major_id;
    this->semester_or_position = semester_or_position;
    this->password = password;
}

bool Person::check_id_conformity(int id)
{
    if (this->id == id)
        return true;
    else return false;
}

bool Person::check_password_conformity(string password)
{
    if (this->password == password)
        return true;
    else return false;
}

void Person::send_post(string title, string message)
{
    int post_id;
    if (posts.size() == 0)
        post_id = 1;
    else
        post_id = posts[posts.size() - 1].post_id + 1;
    posts.push_back({post_id, title, message});
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

bool Person::id_match_then_connect(int id, Person* current_user)
{
    if (this->id == id)
    {
        connect_to_person(current_user);
        return true;
    }
    return false;
}

void Person::connect_to_person(Person* person)
{
    connected_users.push_back(person);
}

bool Person::id_match_then_show_page(int id, vector<Major> majors)
{
    string major;
    for (int i = 0; i < majors.size(); i++)
    {
        if (majors[i].get_id() == major_id)
            major = majors[i].get_name();
    }
    if (this->id == id)
    {
        if (type == "student")
            cout << name << ' ' << major << ' ' << semester_or_position << endl;
        else if (type == "professor")
            cout << name << ' ' << semester_or_position << endl;
        for (int i = posts.size() - 1; i >= 0; i--)
            cout << posts[i].post_id << ' ' << '"' << posts[i].title << '"' << endl;
        return true;
    }
    return false;
}