#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) : vec(other.vec), de(other.de) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        vec = other.vec;
        de = other.de;
    }
    return (*this);
}

PmergeMe::~PmergeMe() {}

void parse_input(const std::string &str)
{
	int skip_plus = str[0] == '+';
	for (int i = skip_plus; i < str.length(); i++)
	{
		if (!std::isdigit(str[i]))
			throw std::invalid_argument("Error: Invalid input provided.");
	}
}

void PmergeMe::process_input(int ac, char **av)
{
    for (int i = 1; i < ac; i++)
    {
		parse_input(av[i]);
		int value = std::atoi(av[i]);
		vec.push_back(value);
		de.push_back(value);
    }
}

void PmergeMe::sort_and_display()
{
}