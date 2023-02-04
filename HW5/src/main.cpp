#include <array>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>

namespace {

bool not_getline(std::istream * input, std::string & str)
{
    return !std::getline(*input, str);
}

void comm_output(std::string & str, std::array<bool, 3> const & args, size_t numOfCol)
{
    if (!args[numOfCol - 1]) {
        for (size_t i = 0; i < numOfCol - 1; i++) {
            if (!args[i])
                std::cout << '\t';
        }
        std::cout << str << '\n';
    }
}

void comm_stream(std::istream * input1, std::istream * input2, std::array<bool, 3> args)
{
    std::string str1;
    std::string str2;
    bool input1end = not_getline(input1, str1);
    bool input2end = not_getline(input2, str2);

    while (!input1end || !input2end) {
        int compareStr = str1.compare(str2);
        if ((compareStr < 0 && !input1end) || input2end) {
            comm_output(str1, args, 1);
            input1end = not_getline(input1, str1);
        }
        else if (compareStr > 0 || input1end) {
            comm_output(str2, args, 2);
            input2end = not_getline(input2, str2);
        }
        else if (compareStr == 0) {
            comm_output(str1, args, 3);
            input1end = not_getline(input1, str1);
            input2end = not_getline(input2, str2);
        }
    }
    if (input1 != &std::cin) {
        delete input1;
    }
    if (input2 != &std::cin) {
        delete input2;
    }
}

std::istream * getInput(const char * str)
{
    return std::string_view(str) != "-" ? new std::ifstream(str) : &std::cin;
}
} // namespace

int main(int argc, char ** argv)
{
    std::array<bool, 3> args = {false, false, false};
    size_t numName1 = 1;
    for (int i = 1; i < argc; ++i) {
        size_t len = std::strlen(argv[i]);
        if (argv[i][0] == '-' && len != 1) {
            numName1++;
            for (auto el : std::string_view(argv[i], len).substr(1)) {
                args[el - '1'] = true;
            }
        }
    }
    comm_stream(getInput(argv[numName1]), getInput(argv[numName1 + 1]), args);

    return 0;
}
