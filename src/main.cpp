#include "system.hpp"

int main(int argc, char *argv[])
{
    System* system = read_files(argv);
    //system->answer_command();
    delete system;
    return 0;
}