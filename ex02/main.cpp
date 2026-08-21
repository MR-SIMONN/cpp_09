#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    if (ac < 3)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    PmergeMe pmergeMe;

    try
    {
        pmergeMe.run_algorithm(ac, av);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

}