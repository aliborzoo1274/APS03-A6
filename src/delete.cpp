#include "system.hpp"

void System::delete_method()
{
    string command;
    char question_mark;
    cin >> command;
    cin >> question_mark;
    if (question_mark != '?')
        error("Bad Request");
    if (command != "post" && command != "my_courses")
        error("Not Found");
    if (current_user == nullptr)
        error("Permission Denied");
    if (command == "post")
        delete_post();
    else if (command == "my_courses")
        delete_my_courses();
}

void System::delete_post()
{
    int post_id;
    bool id_in_line_found = false;
    bool id_found = false;
    vector<string> words = read_line();
    for (int i = 0; i < words.size(); i++)
    {
        if (words[i] == "id" && !id_in_line_found)
        {
            id_in_line_found = true;
            post_id = string_to_int(words[i + 1]);
        }
    }
    if (!id_in_line_found)
        error("Bad Request");
    if (current_user->has_post_id_then_delete(post_id))
        id_found = true;
    if (!id_found)
        error("Not Found");
    order_done("OK");
}

void System::delete_my_courses()
{
    int course_id;
    bool id_in_line_found = false;
    bool id_found = false;
    auto student = dynamic_pointer_cast<Student>(current_user);
    if (student == nullptr)
        error("Permission Denied");
    vector<string> words = read_line();
    for (int i = 0; i < words.size(); i++)
    {
        if (words[i] == "id" && !id_in_line_found)
        {
            id_in_line_found = true;
            course_id = string_to_int(words[i + 1]);
        }
    }
    if (!id_in_line_found)
        error("Bad Request");
    if (student->has_course_id_then_delete(course_id))
        id_found = true;
    if (!id_found)
        error("Not Found");
    order_done("OK");
}