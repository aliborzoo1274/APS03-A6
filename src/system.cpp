#include "system.hpp"

System::System(vector<Major> majors, vector<Person> persons, vector<Course> courses)
{
    this->majors = majors;
    this->persons = persons;
    this->courses = courses;
}

void System::answer_command()
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
    {
        cerr << "Bad Request" << endl;
        answer_command();
    }
}

void System::get_method() {cout << "Hi" << endl;}

void System::post_method()
{
    string command;
    char question_mark;
    cin >> command;
    cin >> question_mark;
    if (command == "login")
        post_login();
}

void System::put_method() {}

void System::delete_method() {}

void System::post_login() {}
// {
//     string word, id, password;
//     vector<string> words;
//     while (cin)
//         words.push_back(word);
//     for (int i = 0; i < words.size(); i++)
//     {
//         if (words[i] == "id")
//             id = words[i + 1];
//         if (words[i] == "password")
//             password = words[i + 1];
//     }
//     for (int i = 0; i < students.size(); i++)
//     {
//         if (students[i].check_id_conformity(id))
//         {
//             if (students[i].check_password_conformity(password))
//                 current_user = student
//         }
//     }
// }