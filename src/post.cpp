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
        else if (command != "logout" && command != "post" &&
                 command != "connect" && command != "course_offer")
            error("Not Found");
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
        else if (command == "course_offer")
        {
            if (!current_user->is_admin())
                error("Permission Denied");
            post_course_offer();
        }
        else
            error("Not Found");
    }
}

void System::post_login()
{
    int id;
    string password;
    bool id_in_line_found = false;
    bool person_found = false;
    bool password_in_line_found = false;
    bool person_is_allowed = false;
    vector<string> words = read_line();
    for (int i = 0; i < words.size(); i++)
    {
        if (words[i] == "id" && !id_in_line_found)
        {
            id_in_line_found = true;
            id = string_to_int(words[i + 1]);
        }
        else if (words[i] == "password" && !password_in_line_found)
        {
            password_in_line_found = true;
            password = words[i + 1];
        }
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
    if (!id_in_line_found || !password_in_line_found)
        error("Bad Request");
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
    string image_address = "empty";
    bool title_found = false;
    bool message_found = false;
    bool image_found = false;
    vector<string> words = read_line();
    for (int i = 0; i < words.size(); i++)
    {
        if (words[i] == "title" && !title_found)
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
        else if (words[i] == "message" && !message_found)
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
        else if (words[i] == "image" && !image_found)
        {
            image_found = true;
            image_address = words[i + 1];
        }
    }
    if (!title_found || !message_found)
        error("Bad Request");
    current_user->send_post(title, message, image_address);
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
        if (words[i] == "id" && !id_in_line_found)
        {
            id_in_line_found = true;
            person_id = string_to_int(words[i + 1]);
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

void System::post_course_offer()
{
    int course_id, professor_id, capacity, class_number;
    Time time;
    Date exam_date;
    Person* professor = nullptr;
    bool course_id_in_line_found = false;
    bool course_id_found = false;
    bool professor_id_in_line_found = false;
    bool person_id_found = false;
    bool professor_id_found = false;
    bool professor_can_offer_course = false;
    bool capacity_in_line_found = false;
    bool time_in_line_found = false;
    bool exam_date_in_line_found = false;
    bool class_number_in_line_found = false;
    vector<string> words = read_line();
    for (int i = 0; i < words.size(); i++)
    {
        if (words[i] == "course_id" && !course_id_in_line_found)
        {
            course_id_in_line_found = true;
            course_id = string_to_int(words[i + 1]);
        }
        else if (words[i] == "professor_id" && !professor_id_in_line_found)
        {
            professor_id_in_line_found = true;
            professor_id = string_to_int(words[i + 1]);
        }
        else if (words[i] == "capacity" && !capacity_in_line_found)
        {
            capacity_in_line_found = true;
            capacity = string_to_int(words[i + 1]);
        }
        else if (words[i] == "time" && !time_in_line_found)
        {
            time_in_line_found = true;
            time = adjust_time(words[i + 1]);
        }
        else if (words[i] == "exam_date" && !exam_date_in_line_found)
        {
            exam_date_in_line_found = true;
            exam_date = adjust_date(words[i + 1]);
        }
        else if (words[i] == "class_number" && !class_number_in_line_found)
        {
            class_number_in_line_found = true;
            class_number = string_to_int(words[i + 1]);
        }
    }
    for (int i = 0; i < persons.size(); i++)
    {
        if (persons[i].id_match(professor_id))
        {
            person_id_found = true;
            if (persons[i].is_professor())
            {
                professor_id_found = true;
                professor = &persons[i];
                for (int j = 0; j < courses.size(); j++)
                {
                    if (courses[j].id_match(course_id))
                    {
                        course_id_found = true;
                        Course* course = new Course(courses[j]);
                        course->set_information(professor, capacity, class_number, time, exam_date, unique_course_id_counter);
                        if (course->is_in_this_major(professor->get_major_id()) && !professor->is_busy(course))
                        {
                            professor_can_offer_course = true;
                            offered_courses.push_back(course);
                            professor->set_course(course);
                            current_user->course_offering(professor);
                            unique_course_id_counter++;
                        }
                        else delete course;
                    }
                }
            }
        }
    }
    if (!course_id_in_line_found || !professor_id_in_line_found ||
        !capacity_in_line_found || !time_in_line_found ||
        !exam_date_in_line_found || !class_number_in_line_found)
        error("Bad Request");
    if (!course_id_found || !person_id_found)
        error("Not Found");
    if (!professor_id_found || !professor_can_offer_course)
        error("Permission Denied");
    order_done ("OK");
}