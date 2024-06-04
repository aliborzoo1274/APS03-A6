#pragma once
#include "global.hpp"
#include "professor.hpp"

struct Course_channel_post
{
    Post post;
    string author_name;
};

class Person;

class Course
{
public:
    Course(int cid, string name, int credit, int prerequisite, vector<int> majors_id);
    bool id_match(int id);
    bool unique_id_match(int id);
    bool is_in_this_major(int id);
    void set_information(shared_ptr<Professor> professor, int capacity, int class_number, Time time, Date exam_date, int unique_id);
    void add_person(shared_ptr<Person> person);
    bool has_conflict(shared_ptr<Course> course);
    bool prerequisite_met(int semester);
    void print(string called_by);
    void send_course_post(Person* author, string title, string message, string image_address);
    string get_name();
    Date get_exam_date();
private:
    int cid;
    int unique_id;
    int unique_id_counter = 1;
    int num_of_course_posts = 1;
    shared_ptr<Professor> professor = nullptr;
    vector<shared_ptr<Person>> persons;
    vector<Course_channel_post> channel_posts;
    int capacity;
    int class_number;
    string name;
    int credit;
    int prerequisite;
    vector<int> majors_id;
    Time time;
    Date exam_date;
};