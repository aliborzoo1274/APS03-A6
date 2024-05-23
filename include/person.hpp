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
    void print_posts()
    {
        for (auto i : posts)
            cout << i.title << ' ' << i.message << ' ' << i.post_id << endl;
    }
private:
    string type;
    int id;
    string name;
    int major_id;
    string semester_or_position;
    string password;
    vector<Post> posts;
};