#pragma once
#include "global.hpp"

class Person;

class User
{
public:
    User(int id, string name, string password);
    bool id_match(int id);
    bool password_match(string password);
    void send_post(string title, string message, string image_address);
    bool has_post_id_then_delete(int id);
    bool connected_before_to_you(int id);
    void connect_to_person(shared_ptr<Person> person);
    virtual void show_page();
    virtual bool has_post_then_show_it(int id);
    void set_profile_photo(string photo_address);
private:
    string password;
    string profile_photo_address;
protected:
    int id;
    string name;
    int num_of_posts = 1;
    vector<Post> posts;
    vector<shared_ptr<Person>> connected_users;
    virtual void print_inf() = 0;
    virtual void show_posts();
    void send_notification(int id, string name, string message);
};