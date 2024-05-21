#include "read_files.hpp"

System* read_files(char* argv[])
{
    ifstream majors(argv[1]);
    vector<Major> majors_list = read_majors_file(majors);
    majors.close();
    ifstream students(argv[2]);
    vector<Student> student_list = read_students_file(students);
    students.close();
    ifstream courses(argv[3]);
    vector<Course> course_list = read_courses_file(courses);
    courses.close();
    ifstream professors(argv[4]);
    vector<Professor> professor_list = read_professors_file(professors);
    professors.close();
    System* system = new System(majors_list, student_list, course_list, professor_list);
    return system;
}

vector<Major> read_majors_file(ifstream& majors)
{
    vector<Major> majors_list;
    bool is_first_line = true;
    int mid;
    int parameter_counter;
    string name;
    string line, line_parameter;
    while (getline(majors, line))
    {
        parameter_counter = 0;
        if (is_first_line)
        {
            is_first_line = false;
            continue;
        }
        stringstream line_stream(line);
        while (getline(line_stream, line_parameter, FIRST_DELIM))
        {
            if (parameter_counter == 0)
                mid = stoi(line_parameter);
            else
            {
                name = line_parameter;
                majors_list.push_back({mid, name});
            }
            parameter_counter++;
        }
    }
    return majors_list;
}

vector<Student> read_students_file(ifstream& students)
{
    vector<Student> studens_list;
    bool is_first_line = true;
    int sid, major_id, semester;
    int parameter_counter;
    string name, password;
    string line, line_parameter;
    while (getline(students, line))
    {
        parameter_counter = 0;
        if (is_first_line)
        {
            is_first_line = false;
            continue;
        }
        stringstream line_stream(line);
        while (getline(line_stream, line_parameter, FIRST_DELIM))
        {
            switch (parameter_counter)
            {
            case 0:
                sid = stoi(line_parameter);
                break;
            case 1:
                name = line_parameter;
                break;
            case 2:
                major_id = stoi(line_parameter);
                break;
            case 3:
                semester = stoi(line_parameter);
                break;
            default:
                password = line_parameter;
                studens_list.push_back({sid, name, major_id, semester, password});
                break;
            }
            parameter_counter++;
        }
    }
    return studens_list;
}

vector<Course> read_courses_file(ifstream& courses)
{
    vector<Course> courses_list;
    bool is_first_line = true;
    int cid, credit, prerequisite;
    vector<int> majors_id;
    int parameter_counter;
    string name;
    string line, line_parameter, majors_id_parameter;
    while (getline(courses, line))
    {
        parameter_counter = 0;
        majors_id.clear();
        if (is_first_line)
        {
            is_first_line = false;
            continue;
        }
        stringstream line_stream(line);
        while (getline(line_stream, line_parameter, FIRST_DELIM))
        {
            switch (parameter_counter)
            {
            case 0:
                cid = stoi(line_parameter);
                break;
            case 1:
                name = line_parameter;
                break;
            case 2:
                credit = stoi(line_parameter);
                break;
            case 3:
                prerequisite = stoi(line_parameter);
                break;
            default:
                stringstream majors_id_stream(line_parameter);
                while (getline(majors_id_stream, majors_id_parameter, SECOND_DELIM))
                    majors_id.push_back(stoi(majors_id_parameter));
                courses_list.push_back({cid, name, credit, prerequisite, majors_id});
                break;
            }
            parameter_counter++;
        }
    }
    return courses_list;
}

vector<Professor> read_professors_file(ifstream& professors)
{
    vector<Professor> professors_list;
    bool is_first_line = true;
    int pid, major_id;
    int parameter_counter;
    string name, position, password;
    string line, line_parameter;
    while (getline(professors, line))
    {
        parameter_counter = 0;
        if (is_first_line)
        {
            is_first_line = false;
            continue;
        }
        stringstream line_stream(line);
        while (getline(line_stream, line_parameter, FIRST_DELIM))
        {
            switch (parameter_counter)
            {
            case 0:
                pid = stoi(line_parameter);
                break;
            case 1:
                name = line_parameter;
                break;
            case 2:
                major_id = stoi(line_parameter);
                break;
            case 3:
                position = line_parameter;
                break;
            default:
                password = line_parameter;
                professors_list.push_back({pid, name, major_id, position, password});
                break;
            }
            parameter_counter++;
        }
    }
    return professors_list;
}