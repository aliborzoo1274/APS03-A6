#include "global.hpp"
#include "majors.hpp"
#include "students.hpp"
#include "courses.hpp"
#include "professors.hpp"

class System
{
public:

private:
    vector<Major*> majors;
    vector<Student*> students;
    vector<Course*> courses;
    vector<Professor*> professors;
};