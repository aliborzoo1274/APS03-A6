#include "course.hpp"

Course::Course(int cid, string name, int credit, int prerequisite, vector<int> majors_id)
{
    this->cid = cid;
    this->name = name;
    this->credit = credit;
    this->prerequisite = prerequisite;
    this->majors_id = majors_id;
}

bool Course::id_match(int id)
{
    if (cid == id)
        return true;
    else return false;
}

bool Course::unique_id_match(int id)
{
    if (unique_id == id)
        return true;
    else return false;
}

bool Course::is_in_this_major(int id)
{
    for (int i = 0; i < majors_id.size(); i++)
    {
        if (id == majors_id[i])
            return true;
    }
    return false;
}

void Course::set_information(Person* professor, int capacity, int class_number, Time time, Date exam_date, int unique_id)
{
    this->professor = professor;
    this->capacity = capacity;
    this->class_number = class_number;
    this->time = time;
    this->exam_date = exam_date;
    this->unique_id = unique_id;
}

bool Course::has_conflict(Course* course)
{
    if (time.week_day == course->time.week_day)
    {
        if (time.start_time == course->time.start_time)
            return true;
        else if (time.start_time < course->time.start_time)
        {
            if (time.end_time > course->time.start_time)
                return true;
        }
        else
        {
            if (course->time.end_time > time.start_time)
                return true;
        }
    }
    return false;
}

bool Course::prerequisite_met(string semester)
{
    if (stoi(semester) >= prerequisite)
        return true;
    else return false;
}

void Course::print(string p_name)
{
    cout << cid << ' ' << name << ' ' << capacity << ' ' << p_name << ' ' <<
    time.week_day << ':' << time.start_time << '-' << time.end_time << ' ' <<
    exam_date.year << '/' << exam_date.month << '/' << exam_date.day << ' ' << class_number << endl;
}

Date Course::get_exam_date()
{
    return exam_date;
}

Person* Course::get_professor()
{
    return professor;
}