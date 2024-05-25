#pragma once
#include "global.hpp"

struct Post
{
    int post_id;
    string title;
    string message;
};


class Person
{
public:
    Person(string type, int id, string name, int major_id, string semester_or_position, string password);
    bool check_id_conformity(int id);
    bool check_password_conformity(string password);
    void send_post(string title, string message);
    bool has_post_id_then_delete(int id);
    bool connected_before_to_you(int id);
    bool id_match_then_connect(int id, Person* current_user);
    void connect_to_person(Person* person);
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
    string semester_or_position;
    string password;
    vector<Post> posts;
    vector<Person*> connected_users;
};