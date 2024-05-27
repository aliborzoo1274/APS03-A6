#include "system.hpp"

System::System(vector<Major> majors, vector<Person> persons, vector<Course> courses)
{
    this->majors = majors;
    this->persons = persons;
    this->courses = courses;
}

void System::answer_command()
{
    while (TRUE)
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
                    error("Bad Request");
            }
            else
            {
                if (command_method == "POST")
                    post_method();
                else if (command_method != "GET" && command_method != "PUT" &&
                         command_method != "DELETE")
                    error("Bad Request");
                else
                    error("Permission Denied");
            }
        }
        catch (const runtime_error& e)
        {
            cerr << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

vector<string> System::read_line()
{
    string word;
    vector<string> words;
    while (cin.peek() != '\n' && (cin >> word))
        words.push_back(word);
    return words;
}

void System::order_done(string message)
{
    if (message == "OK")
        cout << "OK" << endl;
    else if (message == "Empty")
        cout << "Empty" << endl;
}

void System::error(string message)
{
    if (message == "Bad Request")
        throw runtime_error("Bad Request");
    else if (message == "Not Found")
        throw runtime_error("Not Found");
    else if (message == "Permission Denied");
        throw runtime_error("Permission Denied");
}

bool System::connected_before(int id)
{
    if (current_user->connected_before_to_you(id))
        return true;
    return false;
}

bool System::has_person_id_then_connect(int id)
{
    for (int i = 0; i < persons.size(); i++)
    {
        if (persons[i].id_match(id))
        {
            current_user->connect_to_person(&persons[i]);
            persons[i].connect_to_person(current_user);
            return true;
        }
    }
    return false;
}

bool System::has_person_id_then_show_page(int id)
{
    for (int i = 0; i < persons.size(); i++)
    {
        if (persons[i].id_match(id))
        {
            persons[i].show_page();
            return true;
        }
    }
    return false;
}

bool System::has_person_id_and_post_id_then_show_post(int person_id, int post_id)
{
    for (int i = 0; i < persons.size(); i++)
    {
        if (persons[i].id_match(person_id))
        {
            if (persons[i].has_post_then_show_it(post_id))
                return true;
        }
    }
    return false;
}