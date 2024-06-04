#include "system.hpp"

void System::get_method()
{
    string command;
    char question_mark;
    cin >> command;
    cin >> question_mark;
    if (question_mark != '?')
        error("Bad Request");
    if (command != "courses" && command != "personal_page" &&
        command != "post" && command != "notification" && command != "my_courses"
        && command != "hey")
        error("Not Found");
    if (current_user == nullptr)
        error("Permission Denied");
    if (command == "courses")
        get_courses();
    else if (command == "personal_page")
        get_personal_page();
    else if (command == "post")
        get_post();
    else if (command == "notification")
        get_notif();
    else if (command == "my_courses")
        get_my_courses();
}

void System::get_courses()
{
    int id;
    bool id_in_line_found = false;
    bool id_found = false;
    vector<string> words = read_line();
    if (words.size() == 0)
    {
        id_in_line_found = true;
        id_found = true;
        if (!has_any_course_show_them())
            order_done("Empty");
    }
    else
    {
        for (int i = 0; i < words.size(); i++)
        {
            if (words[i] == "id" && !id_in_line_found)
            {
                id_in_line_found = true;
                id = string_to_int(words[i + 1]);
            }
        }
    }
    if (!id_in_line_found)
        error("Bad Request");
    if (has_course_id_then_show_inf(id))
        id_found = true;
    if (!id_found)
        error("Not Found");
}

void System::get_personal_page()
{
    int person_id;
    bool id_in_line_found = false;
    bool id_found = false;
    vector<string> words = read_line();
    for (int i = 0; i < words.size(); i++)
    {
        if (words[i] == "id" && !id_in_line_found)
        {
            id_in_line_found = true;
            person_id = string_to_int(words[i + 1]);
        }
    }
    if (!id_in_line_found)
        error("Bad Request");
    if (has_user_id_then_show_page(person_id))
        id_found = true;
    if (!id_found)
        error("Not Found");
}

void System::get_post()
{
    int person_id, post_id;
    bool id_in_line_found = false;
    bool post_id_in_line_found = false;
    bool id_found = false;
    bool post_id_found = false;
    vector<string> words = read_line();
    for (int i = 0; i < words.size(); i++)
    {
        if (words[i] == "id" && !id_in_line_found)
        {
            id_in_line_found = true;
            person_id = string_to_int(words[i + 1]);
            if (person_id < 0)
                error("Bad Request");
        }
        if (words[i] == "post_id" && !post_id_in_line_found)
        {
            post_id_in_line_found = true;
            post_id = string_to_int(words[i + 1]);
            if (post_id <= 0)
                error("Bad Request");
        }
    }
    if (!id_in_line_found || !post_id_in_line_found)
        error("Bad Request");
    if (has_user_id_and_post_id_then_show_post(person_id, post_id))
    {
        id_found = true;
        post_id_found = true;
    }
    if (!id_found || !post_id_found)
        error("Not Found");
}

void System::get_notif()
{
    auto current_person = dynamic_pointer_cast<Person>(current_user);
    if (current_person == nullptr)
        error("Permission Denied");
    if (!current_person->show_notifications())
        order_done("Empty");
}

void System::get_my_courses()
{
    auto student = dynamic_pointer_cast<Student>(current_user);
    if (student == nullptr)
        error("Permission Denied");
    if (!student->show_courses())
        order_done("Empty");
}