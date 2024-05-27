#pragma once
#include "global.hpp"
#include "system.hpp"

struct Post
{
    int post_id;
    string title;
    string message;
};

struct Notification
{
    int person_id;
    string person_name;
    string message;
};

class Person
{
public:
    Person(string type, int id, string name, int major_id, string major_name, string semester_or_position, string password);
    bool id_match(int id);
    bool password_match(string password);
    void send_post(string title, string message);
    bool has_post_id_then_delete(int id);
    bool connected_before_to_you(int id);
    void connect_to_person(Person* person);
    void show_page();
    bool has_post_then_show_it(int id);
    bool show_notifications();
    void print_connected()
    {
        for (auto i : connected_users)
            cout << i->id << ' ' << i->name << ' ' << i->password << endl;
    }
    void get_inf()
    {
        cout << type << ' ' << id << endl;
    }
private:
    string type;
    int id;
    string name;
    int major_id;
    string major_name;
    string semester_or_position;
    string password;
    vector<Post> posts;
    int num_of_posts = 1;
    vector<Person*> connected_users;
    vector<Notification> notifications;
};