#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <exception>
#include <cstdlib>

class PmergeMe
{
    private:
        std::vector<int> vec;
        std::deque<int> de;
    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();

        void process_input(int ac, char **av);
        void sort_and_display();

};

#endif