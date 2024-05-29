#pragma once
#include "global.hpp"
#include "read_files.hpp"
#include "major.hpp"
#include "course.hpp"
#include "person.hpp"

class System
{
public:
    System(vector<Major> majors, vector<Person> persons, vector<Course> courses);
    void answer_command();
private:
    vector<Major> majors;
    vector<Person> persons;
    vector<Course> courses;
    vector<Course*> offered_courses;
    int unique_course_id_counter = 1;
    Person* current_user = nullptr;
    vector<string> read_line();
    int string_to_int(string s);
    Time adjust_time(string time_string);
    Date adjust_date(string date_string);
    void order_done(string message);
    void error(string message);
    void get_method();
    void get_personal_page();
    void get_post();
    void get_notif();
    void get_my_courses();
    void post_method();
    void post_login();
    void post_logout();
    void post_post();
    void post_connect();
    void post_course_offer();
    void put_method();
    void put_my_courses();
    void delete_method();
    void delete_post();
    void delete_my_courses();
    bool connected_before(int id);
    bool has_person_id_then_connect(int id);
    bool has_person_id_then_show_page(int id);
    bool has_person_id_and_post_id_then_show_post(int person_id, int post_id);
    Course* get_course(int id);
};