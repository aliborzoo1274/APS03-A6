#pragma once
#include "global.hpp"

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

class Course;

class Person
{
public:
    Person(string type, int id, string name, int major_id, string major_name, string semester_or_position, string password);
    Person(string type, int id, string name, string password);
    bool id_match(int id);
    bool password_match(string password);
    bool is_admin();
    bool is_student();
    bool is_professor();
    void send_post(string title, string message);
    void send_notification(int id, string name, string message);
    bool has_post_id_then_delete(int id);
    bool connected_before_to_you(int id);
    void connect_to_person(Person* person);
    void show_page();
    bool has_post_then_show_it(int id);
    bool show_notifications();
    void course_offering(Person* professor);
    void set_course(Course* course);
    bool is_busy(Course* course);
    bool has_exam_date_conflict(Date date);
    void get_course();
    int get_major_id();
    string get_semester_or_position();
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
    vector<Course*> courses;
};