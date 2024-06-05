#pragma once
#include "global.hpp"
#include "person.hpp"

struct TA_form
{
    int post_id;
    shared_ptr<Course> course;
    string message;
};

class Professor : public Person
{
public:
    Professor(int id, string name, int major_id, string major_name, string position, string password);
    void send_ta_post(shared_ptr<Course> course, string message);
    void show_posts();
    bool has_post_then_show_it(int id);
    shared_ptr<Course> get_ta_form_course(int form_id);
    string get_position();
private:
    string position;
    void print_spec();
    vector<TA_form> ta_posts;
};