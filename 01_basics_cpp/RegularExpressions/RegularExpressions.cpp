#include <iostream>
#include <regex>

using namespace std;

int main()
{
    std::string input;

    std::regex pattern;
    pattern = std::regex("[0-9A-D]+");

	std::cin >> input;

    if (std::regex_match(input, pattern))
    {
        std::cout << "The input is a valid number." << std::endl;
    }
    else
    {
        std::cout << "The input is not a valid number." << std::endl;
    }
}
