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
                 command != "connect" && command != "course_offer" &&
                 command != "profile_photo" && command != "course_post" &&
                 command != "ta_form" && command != "ta_request" &&
                 command != "close_ta_form")
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
            post_course_offer();
        else if (command == "profile_photo")
            post_profile_photo();
        else if (command == "course_post")
            post_course_post();
        else if (command == "ta_form")
            post_ta_form();
        else if (command == "ta_request")
            post_ta_request();
        else if (command == "close_ta_form")
            post_close_ta_form();
        else
            error("Not Found");
    }
}

void System::post_login()
{
    int id;
    string password;
    bool id_in_line_found = false;
    bool user_found = false;
    bool password_in_line_found = false;
    bool user_is_allowed = false;
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
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->id_match(id))
        {
            user_found = true;
            if (users[i]->password_match(password))
            {
                user_is_allowed = true;
                current_user = users[i];
                order_done("OK");
            }
        }
    }
    if (!id_in_line_found || !password_in_line_found)
        error("Bad Request");
    if (!user_found)
        error("Not Found");
    else
    {
        if (!user_is_allowed)
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
    bool course_id_in_line_found = false;
    bool course_id_found = false;
    bool professor_id_in_line_found = false;
    bool user_id_found = false;
    bool professor_id_found = false;
    bool professor_can_offer_course = false;
    bool capacity_in_line_found = false;
    bool time_in_line_found = false;
    bool exam_date_in_line_found = false;
    bool class_number_in_line_found = false;
    auto admin = dynamic_pointer_cast<Admin>(current_user);
    if (admin == nullptr)
        error("Permission Denied");
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
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->id_match(professor_id))
        {
            user_id_found = true;
            auto professor = dynamic_pointer_cast<Professor>(users[i]);
            if (professor != nullptr)
            {
                professor_id_found = true;
                for (int j = 0; j < courses.size(); j++)
                {
                    if (courses[j].id_match(course_id))
                    {
                        course_id_found = true;
                        auto course = make_shared<Course>(courses[j]);
                        course->set_information(professor, capacity, class_number, time, exam_date, unique_course_id_counter);
                        course->add_person(professor);
                        if (course->is_in_this_major(professor->get_major_id()) && !professor->has_time_conflict(course))
                        {
                            professor_can_offer_course = true;
                            offered_courses.push_back(course);
                            professor->take_course(course);
                            admin->course_offering(professor);
                            unique_course_id_counter++;
                        }
                    }
                }
            }
        }
    }
    if (!course_id_in_line_found || !professor_id_in_line_found ||
        !capacity_in_line_found || !time_in_line_found ||
        !exam_date_in_line_found || !class_number_in_line_found)
        error("Bad Request");
    if (!course_id_found || !user_id_found)
        error("Not Found");
    if (!professor_id_found || !professor_can_offer_course)
        error("Permission Denied");
    order_done ("OK");
}

void System::post_profile_photo()
{
    bool photo_found;
    vector<string> words = read_line();
    for (int i = 0; i < words.size(); i++)
    {
        if (words[i] == "photo" && !photo_found)
        {
            photo_found = true;
            current_user->set_profile_photo(words[i + 1]);
        }
    }
    if (!photo_found)
        error("Bad Request");
}

void System::post_course_post()
{
    int id;
    string title, message;
    string image_address = "empty";
    bool id_in_line_found = false;
    bool title_found = false;
    bool message_found = false;
    bool image_found = false;
    vector<string> words = read_line();
    for (int i = 0; i < words.size(); i++)
    {
        if (words[i] == "id" && !id_in_line_found)
        {
            id_in_line_found = true;
            id = string_to_int(words[i + 1]);
        }
        else if (words[i] == "title" && !title_found)
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
    if (!title_found || !message_found || !id_in_line_found)
        error("Bad Request");
    if (!has_course_id(id))
        error("Not Found");
    auto person = dynamic_pointer_cast<Person>(current_user);
    if (person == nullptr || !person->allowed_then_course_post(id, title, message, image_address))
        error("Permission Denied");
    order_done("OK");
}

void System::post_ta_form()
{
    int course_id;
    string message;
    bool course_in_line_id_found = false;
    bool message_found = false;
    vector<string> words = read_line();
    for (int i = 0; i < words.size(); i++)
    {
        if (words[i] == "course_id" && !course_in_line_id_found)
        {
            course_in_line_id_found = true;
            course_id = string_to_int(words[i + 1]);
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
    }
    if (!course_in_line_id_found || !message_found)
        error("Bad Request");
    auto course = get_course(course_id);
    if (course == nullptr)
        error("Not Found");
    auto professor = dynamic_pointer_cast<Professor>(current_user);
    if (professor == nullptr || !professor->allowed_to_course(course_id))
        error("Permission Denied");
    professor->send_ta_post(course, message);
    order_done("OK");
}

void System::post_ta_request()
{
    int professor_id, form_id;
    bool professor_id_in_line_found = false;
    bool form_id_in_line_found = false;
    vector<string> words = read_line();
    for (int i = 0; i < words.size(); i++)
    {
        if (words[i] == "professor_id" && !professor_id_in_line_found)
        {
            professor_id_in_line_found = true;
            professor_id = string_to_int(words[i + 1]);
        }
        if (words[i] == "form_id" && !form_id_in_line_found)
        {
            form_id_in_line_found = true;
            form_id = string_to_int(words[i + 1]);
        }
    }
    if (!professor_id_in_line_found || !form_id_in_line_found)
        error("Bad Request");
    auto professor = get_professor(professor_id);
    if (professor == nullptr)
        error("Not Found");
    auto course = professor->get_ta_form_course(form_id);
    if (course == nullptr)
        error("Not Found");
    auto student = dynamic_pointer_cast<Student>(current_user);
    if (student == nullptr || !course->has_ta_prerequisite_then_accept(student))
        error("Permission Denied");
    order_done("OK");
}

void System::post_close_ta_form()
{
    int form_id;
    bool id_in_line_found = false;
    vector<string> words = read_line();
    for (int i = 0; i < words.size(); i++)
    {
        if (words[i] == "id" && !id_in_line_found)
        {
            id_in_line_found = true;
            form_id = string_to_int(words[i + 1]);
        }
    }
    if (!id_in_line_found)
        error("Bad Request");
    auto professor = dynamic_pointer_cast<Professor>(current_user);
    if (professor == nullptr)
        error("Permission Denied");
    auto course = professor->get_ta_form_course(form_id);
    if (course == nullptr)
        error("Not Found");
    course->answer_ta_requests();
    professor->delete_ta_form(form_id);
}