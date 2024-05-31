#include "system.hpp"

void System::put_method()
{
    string command;
    char question_mark;
    cin >> command;
    cin >> question_mark;
    if (question_mark != '?')
        error("Bad Request");
    if (command != "my_courses")
        error("Not Found");
    if (current_user == nullptr)
        error("Permission Denied");
    if (command == "my_courses")
    {
        if (!current_user->is_student())
            error("Permission Denied");
        put_my_courses();
    }
}

void System::put_my_courses()
{
    int course_id;
    Course* course = nullptr;
    bool id_in_line_found = false;
    bool id_found = false;
    bool student_can_take_course = false;
    vector<string> words = read_line();
    for (int i = 0; i < words.size(); i++)
    {
        if (words[i] == "id" && !id_in_line_found)
        {
            id_in_line_found = true;
            course_id = string_to_int(words[i + 1]);
            course = get_course(course_id);
            if (course != nullptr)
            {
                id_found = true;
                if (course->prerequisite_met(current_user->get_semester_or_position()) &&
                    course->is_in_this_major(current_user->get_major_id()) &&
                    !current_user->is_busy(course) && !current_user->has_exam_date_conflict(course->get_exam_date()))
                {
                    student_can_take_course = true;
                    current_user->set_course(course);
                    current_user->get_course();
                }
            }
        }
    }
    if (!id_in_line_found)
        error("Bad Request");
    if (!id_found)
        error("Not Found");
    if (!student_can_take_course)
        error("Permission Denied");
    order_done("OK");
}