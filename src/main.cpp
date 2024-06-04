#include "system.hpp"

int main(int argc, char *argv[])
{
    shared_ptr<System> system = read_files(argv);
    system->answer_command();
    return 0;
}