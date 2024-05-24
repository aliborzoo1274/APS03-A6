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

