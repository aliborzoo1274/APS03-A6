#include "user.hpp"
#include "person.hpp"

User::User(int id, string name, string password)
{
    this->id = id;
    this->name = name;
    this->password = password;
}

bool User::id_match(int id)
{
    if (this->id == id)
        return true;
    return false;
}

bool User::password_match(string password)
{
    if (this->password == password)
        return true;
    return false;
}

void User::send_notification(int id, string name, string message)
{
    for (auto c : connected_users)
        c->set_notification(id, name, message);
}

void User::send_post(string title, string message, string image_address)
{
    int post_id = num_of_posts;
    posts.push_back({post_id, title, message, image_address});
    num_of_posts++;
    send_notification(this->id, this->name, "New Post");
}

bool User::has_post_id_then_delete(int id)
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

bool User::connected_before_to_you(int id)
{
    if (!this->id_match(id))
    {
        for (int i = 0; i < connected_users.size(); i++)
        {
            if (connected_users[i]->id_match(id))
                return true;
        }
    }
    else return true;
    return false;
}

void User::connect_to_person(shared_ptr<Person> person)
{
    connected_users.push_back(person);
}

void User::show_page()
{
    print_inf();
    show_posts();
}

bool User::has_post_then_show_it(int id)
{
    for (int i = 0; i < posts.size(); i++)
    {
        if (posts[i].post_id == id)
        {
            print_inf();
            cout << posts[i].post_id << ' ' << '"' << posts[i].title << '"' << ' ' << '"' << posts[i].message << '"' << endl;
            return true;
        }
    }
    return false;
}

void User::show_posts()
{
    for (int i = posts.size() - 1; i >= 0; i--)
        cout << posts[i].post_id << ' ' << '"' << posts[i].title << '"' << endl;
}

void User::set_profile_photo(string photo_address)
{
    profile_photo_address = photo_address;
}