#pragma once
#include "global.hpp"
#include "user.hpp"

class Course;

class Person : public User
{
public:
    Person(int id, string name, int major_id, string major_name, string password);
    void set_notification(int id, string name, string message);
    bool show_notifications();
    bool has_time_conflict(shared_ptr<Course> course);
    void take_course(shared_ptr<Course> course);
    bool show_courses();
    bool allowed_then_course_post(int course_id, string title, string message, string image_address);
    bool allowed_to_course(int id);
    int get_id();
    string get_name();
    int get_major_id();
protected:
    int major_id;
    string major_name;
    vector<Notification> notifications;
    vector<shared_ptr<Course>> courses;
    virtual void print_spec() = 0;
    virtual void print_inf();
    void print_courses();
};