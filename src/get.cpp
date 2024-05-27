#include "system.hpp"

void System::get_method()
{
    string command;
    char question_mark;
    cin >> command;
    cin >> question_mark;
    if (question_mark != '?')
        error("Bad Request");
    if (command == "personal_page")
        get_personal_page();
    else if (command == "post")
        get_post();
    else
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
        if (words[i] == "id")
        {
            id_in_line_found = true;
            if (words[i + 1].find('.') != string::npos)
                error("Bad Request");
            try
            {
                person_id = stoi(words[i + 1]);
            }
            catch (const invalid_argument& e)
            {
                error("Bad Request");
            }
            if (person_id < 0)
                error("Bad Request");
        }
    }
    if (!id_in_line_found)
        error("Bad Request");
    if (has_person_id_then_show_page(person_id))
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
        if (words[i] == "id")
        {
            id_in_line_found = true;
            if (words[i + 1].find('.') != string::npos)
                error("Bad Request");
            try
            {
                person_id = stoi(words[i + 1]);
            }
            catch (const invalid_argument& e)
            {
                error("Bad Request");
            }
            if (person_id <= 0)
                error("Bad Request");
        }
        if (words[i] == "post_id")
        {
            post_id_in_line_found = true;
            if (words[i + 1].find('.') != string::npos)
                error("Bad Request");
            try
            {
                post_id = stoi(words[i + 1]);
            }
            catch (const invalid_argument& e)
            {
                error("Bad Request");
            }
            if (post_id <= 0)
                error("Bad Request");
        }
    }
    if (!id_in_line_found || !post_id_in_line_found)
        error("Bad Request");
    if (has_person_id_and_post_id_then_show_post(person_id, post_id))
    {
        id_found = true;
        post_id_found = true;
    }
    if (!id_found || !post_id_found)
        error("Not Found");
}