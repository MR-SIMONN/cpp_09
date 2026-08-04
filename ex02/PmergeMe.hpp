#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <exception>

class PmergeMe
{
    private:
        std::vector<int> _vector;
        std::deque<int> _deque;
    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        ~PmergeMe();

        void process_input(int ac, char **av);
        void sort_and_display();

};

#endif