#include "course.hpp"
#include "student.hpp"

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

void Course::set_information(shared_ptr<Professor> professor, int capacity, int class_number, Time time, Date exam_date, int unique_id)
{
    this->professor = professor;
    this->capacity = capacity;
    this->class_number = class_number;
    this->time = time;
    this->exam_date = exam_date;
    this->unique_id = unique_id;
}

void Course::add_person(shared_ptr<Person> person)
{
    persons.push_back(person);
}

bool Course::has_conflict(shared_ptr<Course> course)
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

bool Course::prerequisite_met(int semester)
{
    if (semester >= prerequisite)
        return true;
    else return false;
}

void Course::print(string called_by)
{
    cout << unique_id << ' ' << name << ' ' << capacity << ' ' << professor->get_name();
    if (called_by == "system_all")
        cout << endl;
    else if (called_by == "system_single" || called_by == "person")
        cout << ' ' << time.week_day << ':' << time.start_time << '-' << time.end_time << ' ' <<
        exam_date.year << '/' << exam_date.month << '/' << exam_date.day << ' ' << class_number << endl;
}

void Course::send_course_post(Person* author, string title, string message, string image_address)
{
    int post_id = num_of_course_posts;
    num_of_course_posts++;
    Post post = {post_id, title, message, image_address};
    channel_posts.push_back({post, author->get_name()});
    for (int i = 0; i < persons.size(); i++)
    {
        if (persons[i]->get_id() != author->get_id())
            persons[i]->set_notification(unique_id, name, "New Course Post");
    }
}

void Course::show_posts()
{
    print("person");
    for (int i = channel_posts.size() - 1; i >= 0; i--)
    {
        cout << channel_posts[i].post.post_id << ' ' << channel_posts[i].author_name << ' ' <<
        '"' << channel_posts[i].post.title << '"' << endl;
    }
}

bool Course::has_post(int post_id)
{
    for (int i = 0; i < channel_posts.size(); i++)
    {
        if (channel_posts[i].post.post_id == post_id)
            return true;
    }
    return false;
}

void Course::show_post(int id)
{
    for (int i = 0; i < channel_posts.size(); i++)
    {
        if (channel_posts[i].post.post_id == id)
        {
            print("person");
            cout << channel_posts[i].post.post_id << ' ' << channel_posts[i].author_name << ' ' <<
            '"' << channel_posts[i].post.title << '"' << ' ' << '"' << channel_posts[i].post.message << '"' << endl;
        }
    }
}

bool Course::has_ta_prerequisite_then_accept(shared_ptr<Student> student)
{
    if (student->get_semester() > prerequisite)
    {
        ta_requests.push_back(student);
        return true;
    }
    return false;
}

void Course::answer_ta_requests()
{
    string acceptance_result;
    cout << "We have received " << ta_requests.size() << " requests for the teaching assistant position" << endl;
    for (int i = 0; i < ta_requests.size(); i++)
    {
        auto student = ta_requests[i];
        cout << student->get_id() << ' ' << student->get_name() << ' ' << student->get_semester() << ':' << ' ';
        cin >> acceptance_result;
        if (acceptance_result == "accept")
        {
            ta_list.push_back(student);
            add_person(student);
            student->set_notification(unique_id, name,
            "Your request to be a teaching assistant has been accepted.");
        }
        else if (acceptance_result == "reject")
        {
            student->set_notification(unique_id, name,
            "Your request to be a teaching assistant has been rejected.");
        }
        else
        {
            i--;
            continue;
        }
    }
}

bool Course::is_ta(Student* student)
{
    for (int i = 0; i < ta_list.size(); i++)
    {
        if (ta_list[i]->get_id() == student->get_id())
            return true;
    }
    return false;
}

string Course::get_name()
{
    return name;
}

Date Course::get_exam_date()
{
    return exam_date;
}