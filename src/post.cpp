#include "system.hpp"

void System::post_method()
{
    string command;
    char question_mark;
    cin >> command;
    cin >> question_mark;
    if (question_mark != '?')
        error("Bad Request");
    if (current_user == nullptr)
    {
        if (command == "login")
            post_login();
        else
            error("Permission Denied");
    }
    else
    {
        if (command == "login")
            error("Permission Denied");
        else if (command == "logout")
            post_logout();
        else if (command == "post")
            post_post();
        else if (command == "connect")
            post_connect();
        else
            error("Not Found");
    }
}

void System::post_login()
{
    int id;
    string password;
    bool person_found = false;
    bool person_is_allowed = false;
    vector<string> words = read_line();
    for (int i = 0; i < words.size(); i++)
    {
        if (words[i] == "id")
        {
            try
            {
                id = stoi(words[i + 1]);
            }
            catch (const invalid_argument& e)
            {
                error("Bad Request");
            }
        }
        if (words[i] == "password")
            password = words[i + 1];
    }
    for (int i = 0; i < persons.size(); i++)
    {
        if (persons[i].id_match(id))
        {
            person_found = true;
            if (persons[i].password_match(password))
            {
                person_is_allowed = true;
                current_user = &persons[i];
                order_done("OK");
            }
        }
    }
    if (!person_found)
        error("Not Found");
    else
    {
        if (!person_is_allowed)
            error("Permission Denied");
    }
}

void System::post_logout()
{
    current_user = nullptr;
    order_done("OK");
}

void System::post_post()
{
    string title, message;
    bool title_found = false;
    bool message_found = false;
    vector<string> words = read_line();
    for (int i = 0; i < words.size(); i++)
    {
        if (words[i] == "title")
        {
            i++;
            while (i < words.size() && words[i].back() != '"')
                title += words[i++] + ' ';
            if (i < words.size())
                title += words[i];
            if (title.front() == '"' && title.back() == '"')
            {
                title = title.substr(1, title.size() - 2);
                title_found = true;
            }
        }
        else if (words[i] == "message")
        {
            i++;
            while (i < words.size() && words[i].back() != '"')
                message += words[i++] + ' ';
            if (i < words.size())
                message += words[i];
            if (message.front() == '"' && message.back() == '"')
            {
                message = message.substr(1, message.size() - 2);
                message_found = true;
            }
        }
    }
    if (!title_found || !message_found)
        error("Bad Request");
    current_user->send_post(title, message);
    order_done("OK");
}

void System::post_connect()
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
    if (connected_before(person_id))
        error("Bad Request");
    if (has_person_id_then_connect(person_id))
        id_found = true;
    if (!id_found)
        error("Not Found");
    order_done("OK");
}