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
        pmergeMe.run_algorithm(ac, av);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

}