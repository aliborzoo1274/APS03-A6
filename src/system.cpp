#include "system.hpp"

System::System(vector<Major> majors, vector<shared_ptr<Person>> persons, vector<Course> courses)
{
    this->majors = majors;
    this->courses = courses;
    auto admin = make_shared<Admin>(0, ADMIN, ADMIN);
    for (auto person : persons)
    {
        admin->connect_to_person(person);
        users.push_back(person);
    }
    users.push_back(admin);
}

void System::answer_command()
{
    while (TRUE)
    {
        try
        {
            string command_method;
            cin >> command_method;
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
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->id_match(id))
        {
            auto person = dynamic_pointer_cast<Person>(users[i]);
            auto current_person = dynamic_pointer_cast<Person>(current_user);
            if (person == nullptr) continue;
            if (current_person == nullptr) return false;
            current_user->connect_to_person(person);
            person->connect_to_person(current_person);
            return true;
        }
    }
    return false;
}

bool System::has_user_id_then_show_page(int id)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->id_match(id))
        {
            users[i]->show_page();
            return true;
        }
    }
    return false;
}

bool System::has_user_id_and_post_id_then_show_post(int user_id, int post_id)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->id_match(user_id))
        {
            if (users[i]->has_post_then_show_it(post_id))
                return true;
        }
    }
    return false;
}

bool System::has_any_course_show_them()
{
    if (offered_courses.size() == 0)
        return false;
    for (auto course : offered_courses)
        course->print("system_all");
    return true;
}

bool System::has_course_id(int id)
{
    for (int i = 0; i < offered_courses.size(); i++)
    {
        if (offered_courses[i]->unique_id_match(id))
            return true;
    }
    return false;
}

void System::show_course_inf(int id)
{
    for (int i = 0; i < offered_courses.size(); i++)
    {
        if (offered_courses[i]->unique_id_match(id))
            offered_courses[i]->print("system_single");
    }
}

shared_ptr<Course> System::get_course(int id)
{
    for (int i = 0; i < offered_courses.size(); i++)
    {
        if (offered_courses[i]->unique_id_match(id))
            return offered_courses[i];
    }
    return nullptr;
}

shared_ptr<Professor> System::get_professor(int id)
{
    for (int i = 0; i < users.size(); i++)
    {
        auto professor = dynamic_pointer_cast<Professor>(current_user);
        if (professor != nullptr)
        {
            if (professor->id_match(id))
                return professor;
        }
    }
    return nullptr;
}