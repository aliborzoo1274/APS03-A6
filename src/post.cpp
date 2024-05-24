#include "system.hpp"

void System::post_method()
{
    string command;
    char question_mark;
    cin >> command;
    cin >> question_mark;
    if (question_mark != '?')
        throw runtime_error("Bad Request");
    if (current_user == nullptr)
    {
        if (command == "login")
            post_login();
        else
            throw runtime_error("Permission Denied");
    }
    else
    {
        if (command == "login")
            throw runtime_error("Permission Denied");
        else if (command == "logout")
        {
            current_user = nullptr;
            order_done();
        }
        else if (command == "post")
            post_post();
        else
            throw runtime_error("Not Found");
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
            id = stoi(words[i + 1]);
        if (words[i] == "password")
            password = words[i + 1];
    }
    for (int i = 0; i < persons.size(); i++)
    {
        if (persons[i].check_id_conformity(id))
        {
            person_found = true;
            if (persons[i].check_password_conformity(password))
            {
                person_is_allowed = true;
                current_user = &persons[i];
                order_done();
            }
        }
    }
    if (!person_found)
        throw runtime_error("Not Found");
    else
    {
        if (!person_is_allowed)
            throw runtime_error("Permission Denied");
    }
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
        throw runtime_error("Bad Request");
    current_user->send_post(title, message);
    order_done();
}

void System::post_connect() {}