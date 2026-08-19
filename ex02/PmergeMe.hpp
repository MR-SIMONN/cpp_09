#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstdlib>
#include <ctime>

class PmergeMe
{
    private:
        std::vector<int> V;
        std::deque<int> D;
        int V_odd_element;
        int D_odd_element;
    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();

        void run_algorithm(int ac, char **av);
        void proccess_V_input(int ac, char **av);
        void proccess_D_input(int ac, char **av);
        void sort_vector();
        void sort_deque();
        void print_vector(const std::string &msg);
        std::vector< std::pair<int, int> > get_V_pairs();
        std::deque< std::pair<int, int> > get_D_pairs();
};

#endif