#include "system.hpp"

System::System(vector<Major> majors, vector<Person> persons, vector<Course> courses)
{
    this->majors = majors;
    this->persons = persons;
    this->courses = courses;
    shared_ptr<Person> admin = make_shared<Person>("admin", 0, ADMIN, ADMIN);
    this->persons.push_back(*admin);
    for (int i = 0; i < this->persons.size() - 1; i++)
        this->persons[this->persons.size() - 1].connect_to_person(&this->persons[i]);
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

int System::string_to_int(string s)
{
    int i;
    if (s.find('.') != string::npos)
        error("Bad Request");
    try
    {
        i = stoi(s);
    }
    catch (const invalid_argument& e)
    {
        error("Bad Request");
    }
    if (i < 0)
        error("Bad Request");
    return i;
}

Time System::adjust_time(string time_string)
{
    string parameter, week_day, s_or_e_time;
    int start_time, end_time;
    bool is_first_word = true;
    stringstream time_stream(time_string);
    while (getline(time_stream, parameter, ':'))
    {
        if (is_first_word)
        {
            week_day = parameter;
            is_first_word = false;
        }
        else
        {
            is_first_word = true;
            stringstream s_or_e_time_stream(parameter);
            while (getline(s_or_e_time_stream, s_or_e_time, '-'))
            {
                if (is_first_word)
                {
                    start_time = stof(s_or_e_time);
                    is_first_word = false;
                }
                else
                    end_time = stof(s_or_e_time);
            }
        }
    }
    return {week_day, start_time, end_time};
}

Date System::adjust_date(string date_string)
{
    int year, month, day;
    int date_parameter_counter = 0;
    string date_parameter;
    stringstream date_stream(date_string);
    while (getline(date_stream, date_parameter, '/'))
    {
        switch (date_parameter_counter)
        {
        case 0:
            year = stoi(date_parameter);
            break;
        case 1:
            month = stoi(date_parameter);
            break;
        case 2:
            day = stoi(date_parameter);
            break;
        default:
            break;
        }
        date_parameter_counter++;
    }
    return {year, month, day};
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

bool System::has_any_course_show_them()
{
    if (offered_courses.size() == 0)
        return false;
    for (int i = 0; i < offered_courses.size(); i++)
    {
        string p_name = offered_courses[i]->get_professor()->get_name();
        offered_courses[i]->print(p_name, "system_all");
    }
    return true;
}

bool System::has_course_id_then_show_inf(int id)
{
    for (int i = 0; i < offered_courses.size(); i++)
    {
        if (offered_courses[i]->id_match(id))
        {
            string p_name = offered_courses[i]->get_professor()->get_name();
            offered_courses[i]->print(p_name, "system_single");
            return true;
        }
    }
    return false;
}

Course* System::get_course(int id)
{
    for (int i = 0; i < offered_courses.size(); i++)
    {
        if (offered_courses[i]->unique_id_match(id))
            return offered_courses[i];
    }
}