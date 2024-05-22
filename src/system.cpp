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
    }
    catch (const runtime_error& e)
    {
        cerr << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        answer_command();
    }
}

void System::get_method() {}

void System::post_method()
{
    string command;
    char question_mark;
    cin >> command;
    cin >> question_mark;
    if (question_mark != '?')
        throw runtime_error("Bad Request");
    if (command == "login")
    {
        if (current_user == nullptr)
            post_login();
        else
            throw runtime_error("Permission Denied");
    }
    else if (command == "logout")
    {
        if (current_user == nullptr)
            throw runtime_error("Permission Denied");
        else
        {
            current_user = nullptr;
            order_done();
        }
    }
    else
        throw runtime_error("Bad Request");
}

void System::put_method() {}

void System::delete_method() {}

void System::post_login()
{
    int id;
    string word, password;
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