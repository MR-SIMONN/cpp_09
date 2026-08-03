#include "RPN.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "Error: Invalid number of arguments." << std::endl;
        return 1;
    }

    calculat_RPN(av[1]);

}