#include "system.hpp"

System::System(vector<Major> majors, vector<Person> persons, vector<Course> courses)
{
    this->majors = majors;
    this->persons = persons;
    this->courses = courses;
}

vector<string> System::read_line()
{
    vector<string> words;
    string line, word;
    if (getline(cin, line))
    {
        stringstream line_stream(line);
        while (line_stream >> word)
            words.push_back(word);
    }
    return words;
}

void System::order_done()
{
    cout << "OK" << endl;
    answer_command();
}

void System::answer_command()
{
    bool keep_going = true;
    while (keep_going)
    {
        try
        {
            string command_method;
            cin >> command_method;
            if (current_user != nullptr)
            {
                if (command_method == "GET")
                    get_method();
                else if (command_method == "POST")
                    post_method();
                else if (command_method == "PUT")
                    put_method();
                else if (command_method == "DELETE")
                    delete_method();
                else
                    throw runtime_error("Bad Request");
            }
            else
            {
                if (command_method == "POST")
                    post_method();
                else if (command_method != "GET" && command_method != "PUT" &&
                        command_method != "DELETE")
                    throw runtime_error("Bad Request");
                else
                    throw runtime_error("Permission Denied");
            }
            keep_going = false;
        }
        catch (const runtime_error& e)
        {
            cerr << e.what() << endl;
        }
    }
}

void System::get_method()
{
    current_user->print_posts();
    answer_command();
}

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

void System::put_method() {}

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