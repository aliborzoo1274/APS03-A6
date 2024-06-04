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
        put_my_courses();
}

void System::put_my_courses()
{
    int course_id;
    auto student = dynamic_pointer_cast<Student>(current_user);
    if (student == nullptr)
        error("Permission Denied");
    shared_ptr<Course> course = nullptr;
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
                if (course->prerequisite_met(student->get_semester()) &&
                    course->is_in_this_major(student->get_major_id()) &&
                    !student->has_time_conflict(course) && !student->has_exam_date_conflict(course->get_exam_date()))
                {
                    student_can_take_course = true;
                    student->take_course(course);
                    course->add_person(student);
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