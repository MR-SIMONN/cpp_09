#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    if (ac < 2)
    {
        std::cerr << "Error: No input provided." << std::endl;
        return 1;
    }

    PmergeMe pmergeMe;

    try
    {
        pmergeMe.process_input(ac, av);
        pmergeMe.sort_and_display();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

}