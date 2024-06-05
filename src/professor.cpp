#include "professor.hpp"
#include "course.hpp"

Professor::Professor(int id, string name, int major_id, string major_name, string position, string password) :
Person(id, name, major_id, major_name, password)
{
    this->position = position;
}

void Professor::print_spec()
{
    cout << name << ' ' << major_name << ' ' << position;
}

void Professor::send_ta_post(shared_ptr<Course> course, string message)
{
    int post_id = num_of_posts;
    ta_posts.push_back({post_id, course, message});
    num_of_posts++;
    send_notification(this->id, this->name, "New Form");
}

void Professor::show_posts()
{
    int newest_post_id = 0;
    for (int i = 0; i < posts.size(); i++)
    {
        if (posts[i].post_id > newest_post_id)
            newest_post_id = posts[i].post_id;
    }
    for (int i = 0; i < ta_posts.size(); i++)
    {
        if (ta_posts[i].post_id > newest_post_id)
            newest_post_id = ta_posts[i].post_id;
    }
    while (newest_post_id > 0)
    {
        for (int i = 0; i < posts.size(); i++)
        {
            if (posts[i].post_id == newest_post_id)
                cout << posts[i].post_id << ' ' << '"' << posts[i].title << '"' << endl;
        }
        for (int i = 0; i < ta_posts.size(); i++)
        {
            if (ta_posts[i].post_id == newest_post_id)
            {
                cout << ta_posts[i].post_id << ' ' <<
                "TA form for " << ta_posts[i].course->get_name() << " course" << endl;
            }
        }
        newest_post_id--;
    }
}

bool Professor::has_post_then_show_it(int id)
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
    for (int i = 0; i < ta_posts.size(); i++)
    {
        if (ta_posts[i].post_id == id)
        {
            print_inf();
            cout << ta_posts[i].post_id << ' ' << "TA form for " << ta_posts[i].course->get_name() << " course" << endl;
            ta_posts[i].course->print("person");
            cout << ta_posts[i].message << endl;
            return true;
        }
    }
    return false;
}

string Professor::get_position()
{
    return position;
}