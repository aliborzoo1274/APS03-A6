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
}

bool Person::has_post_id_then_delete(int id)
{
    bool has_post_id = false;
    for (int i = 0; i < posts.size(); i++)
    {
        if (posts[i].post_id == id)
        {
            has_post_id = true;
            posts.erase(posts.begin() + i);
        }
    }
    return has_post_id;
}