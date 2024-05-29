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

bool Course::is_in_this_major(int id)
{
    for (int i = 0; i < majors_id.size(); i++)
    {
        if (id == majors_id[i])
            return true;
    }
    return false;
}

void Course::set_information(Person* professor, int capacity, int class_number, Time time, Date exam_date)
{
    this->professor = professor;
    this->capacity = capacity;
    this->class_number = class_number;
    this->time = time;
    this->exam_date = exam_date;
    unique_id = unique_id_counter;
    unique_id_counter++;
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