#include "system.hpp"

void System::delete_method()
{
    string command;
    char question_mark;
    cin >> command;
    cin >> question_mark;
    if (question_mark != '?')
        throw runtime_error("Bad Request");
    if (command == "post")
        delete_post();
    else
        throw runtime_error("Not Found");
}

void System::delete_post()
{
    int post_id;
    bool id_in_line_found = false;
    bool id_found = false;
    vector<string> words = read_line();
    for (int i = 0; i < words.size(); i++)
    {
        if (words[i] == "id")
        {
            id_in_line_found = true;
            post_id = stoi(words[i + 1]);
        }
    }
    if (current_user->has_post_id_then_delete(post_id))
        id_found = true;
    if (!id_in_line_found)
        throw runtime_error("Bad Request");
    if (!id_found)
        throw runtime_error("Not Found");
    order_done();
}