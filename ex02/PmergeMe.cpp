#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : V_odd_element(-1), D_odd_element(-1) {}

PmergeMe::PmergeMe(const PmergeMe &other) : V(other.V), D(other.D), V_odd_element(other.V_odd_element), D_odd_element(other.D_odd_element) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        V = other.V;
        D = other.D;
		V_odd_element = other.V_odd_element;
		D_odd_element = other.D_odd_element;
    }
    return (*this);
}

PmergeMe::~PmergeMe() {}

void parse_num(const std::string &str)
{
	int skip_plus = str[0] == '+';
	for (size_t i = skip_plus; i < str.size(); i++)
	{
		if (!std::isdigit(str[i]))
			throw std::invalid_argument("Error");
	}
}

void PmergeMe::proccess_V_input(int ac, char **av)
{
    for (int i = 1; i < ac; i++)
    {
		if (av[i][0] == '\0')
			throw std::invalid_argument("Error");
		parse_num(av[i]);
		long value = std::atol(av[i]);
		if (value > INT_MAX)
			throw std::invalid_argument("Error");
		V.push_back(value);
    }
}

void PmergeMe::proccess_D_input(int ac, char **av)
{
    for (int i = 1; i < ac; i++)
    {
		if (av[i][0] == '\0')
			throw std::invalid_argument("Error");
		parse_num(av[i]);
		long value = std::atol(av[i]);
		if (value > INT_MAX)
			throw std::invalid_argument("Error");
		D.push_back(value);
    }
}

std::vector< std::pair<int, int> > PmergeMe::get_V_pairs()
{
	std::vector< std::pair<int, int> > V_pairs;

	if (V.size() < 2)
		throw std::invalid_argument("Error");
	for (size_t i = 0; i < V.size() - 1; i += 2)
	{
		if (V[i] > V[i + 1])
			V_pairs.push_back(std::make_pair(V[i], V[i + 1]));
		else
			V_pairs.push_back(std::make_pair(V[i + 1], V[i]));
	}
	if (V.size() % 2 != 0)
		V_odd_element = V.back();
	return (V_pairs);
}

std::deque< std::pair<int, int> > PmergeMe::get_D_pairs()
{
	std::deque< std::pair<int, int> > D_pairs;

	if (D.size() < 2)
		throw std::invalid_argument("Error");
	for (size_t i = 0; i < D.size() - 1; i += 2)
	{
		if (D[i] > D[i + 1])
			D_pairs.push_back(std::make_pair(D[i], D[i + 1]));
		else
			D_pairs.push_back(std::make_pair(D[i + 1], D[i]));
	}
	if (D.size() % 2 != 0)
		D_odd_element = D.back();
	return (D_pairs);
}

void sort_V_pairs(std::vector< std::pair<int, int> > &V_pairs)
{
	if (V_pairs.size() == 1)
		return;
	size_t mid = V_pairs.size() / 2;
	std::vector< std::pair<int, int> > left(V_pairs.begin(), V_pairs.begin() + mid);
	std::vector< std::pair<int, int> > right(V_pairs.begin() + mid, V_pairs.end());

	sort_V_pairs(left);
	sort_V_pairs(right);
	
	V_pairs.clear();
	size_t i = 0, j = 0;
	while (i < left.size() && j < right.size())
	{
		if (left[i] < right[j])
			V_pairs.push_back(left[i++]);
		else
			V_pairs.push_back(right[j++]);
	}
	while (i < left.size())
		V_pairs.push_back(left[i++]);
	while (j < right.size())
		V_pairs.push_back(right[j++]);
}

void sort_deque_pairs(std::deque< std::pair<int, int> > &d_pairs)
{
	if (d_pairs.size() == 1)
		return;
	size_t mid = d_pairs.size() / 2;
	std::deque< std::pair<int, int> > left(d_pairs.begin(), d_pairs.begin() + mid);
	std::deque< std::pair<int, int> > right(d_pairs.begin() + mid, d_pairs.end());

	sort_deque_pairs(left);
	sort_deque_pairs(right);
	
	d_pairs.clear();
	size_t i = 0, j = 0;
	while (i < left.size() && j < right.size())
	{
		if (left[i] < right[j])
			d_pairs.push_back(left[i++]);
		else
			d_pairs.push_back(right[j++]);
	}
	while (i < left.size())
		d_pairs.push_back(left[i++]);
	while (j < right.size())
		d_pairs.push_back(right[j++]);
}

std::vector<int> generate_jacobsthal(int size)
{
	std::vector<int> jacobsthal(size);
	jacobsthal[0] = 0;
	if (size > 1)
		jacobsthal[1] = 1;
	for (int i = 2; i < size; i++)
		jacobsthal[i] = jacobsthal[i - 1] + 2 * jacobsthal[i - 2];
	return (jacobsthal);
}

std::vector<int> insert_V_loosers(std::vector< std::pair<int, int> > &V_pairs, int odd_element)
{
	std::vector<int> main_chain;
	std::vector<int> loosers;

	for(size_t i = 0; i < V_pairs.size(); i++)
	{
		main_chain.push_back(V_pairs[i].first);
		loosers.push_back(V_pairs[i].second);
	}
	main_chain.insert(main_chain.begin(), loosers[0]);

	std::vector<int> jacob_sequence = generate_jacobsthal(loosers.size() + 2);

	size_t last_jacob = 1;
	for (size_t i = 2; i < jacob_sequence.size(); ++i) 
	{
		size_t current_jacob = jacob_sequence[i];

		if (current_jacob > loosers.size())
			current_jacob = loosers.size();
		for (size_t j = current_jacob - 1; j >= last_jacob; --j)
		{
			std::vector<int>::iterator limit = std::find(main_chain.begin(), main_chain.end(), V_pairs[j].first);
			std::vector<int>::iterator insert_pos = std::lower_bound(main_chain.begin(), limit, loosers[j]);
			main_chain.insert(insert_pos, loosers[j]);
		}
		last_jacob = current_jacob;
	}
	if (odd_element != -1)
	{
		std::vector<int>::iterator it = std::lower_bound(main_chain.begin(), main_chain.end(), odd_element);
		main_chain.insert(it, odd_element);
	}
	return (main_chain);
}

std::deque<int> insert_deque_loosers(std::deque< std::pair<int, int> > &D_pairs, int odd_element)
{
	std::deque<int> main_chain;
	std::deque<int> loosers;

	for(size_t i = 0; i < D_pairs.size(); i++)
	{
		main_chain.push_back(D_pairs[i].first);
		loosers.push_back(D_pairs[i].second);
	}
	main_chain.insert(main_chain.begin(), loosers[0]);

	std::vector<int> jacob_sequence = generate_jacobsthal(loosers.size() + 2);

	size_t last_jacob = 1;
	for (size_t i = 2; i < jacob_sequence.size(); ++i) 
	{
		size_t current_jacob = jacob_sequence[i];

		if (current_jacob > loosers.size())
			current_jacob = loosers.size();
		for (size_t j = current_jacob - 1; j >= last_jacob; --j)
		{
			std::deque<int>::iterator limit = std::find(main_chain.begin(), main_chain.end(), D_pairs[j].first);
			std::deque<int>::iterator insert_pos = std::lower_bound(main_chain.begin(), limit, loosers[j]);
			main_chain.insert(insert_pos, loosers[j]);
		}
		last_jacob = current_jacob;
	}
	if (odd_element != -1)
	{
		std::deque<int>::iterator it = std::lower_bound(main_chain.begin(), main_chain.end(), odd_element);
		main_chain.insert(it, odd_element);
	}
	return (main_chain);
}	

void PmergeMe::sort_deque()
{
	std::deque< std::pair<int, int> > D_pairs = get_D_pairs();

	sort_deque_pairs(D_pairs);
	D = insert_deque_loosers(D_pairs, D_odd_element);
}

void PmergeMe::sort_vector()
{
	std::vector< std::pair<int, int> > V_pairs = get_V_pairs();

	sort_V_pairs(V_pairs);
	V = insert_V_loosers(V_pairs, V_odd_element);
}

void PmergeMe::print_vector(const std::string &msg)
{
    std::cout << msg;
    for (size_t i = 0; i < V.size(); ++i)
        std::cout << V[i] << " ";

    std::cout << std::endl;
}

void PmergeMe::run_algorithm(int ac, char **av)
{

    clock_t start_vec = clock();
    proccess_V_input(ac, av); 
    
    print_vector("Before: ");
    
    sort_vector();         
    clock_t end_vec = clock();
    
    print_vector("After: ");
    
    double time_vec = static_cast<double>(end_vec - start_vec) / CLOCKS_PER_SEC * 1000.0;

    clock_t start_de = clock();
    proccess_D_input(ac, av); 
    sort_deque();                
    clock_t end_de = clock();
    double time_de = static_cast<double>(end_de - start_de) / CLOCKS_PER_SEC * 1000.0;

    std::cout << "Time to process a range of " << V.size() 
              << " elements with std::vector : " << time_vec << " ms" << std::endl;
              
    std::cout << "Time to process a range of " << D.size() 
              << " elements with std::deque : " << time_de << " ms" << std::endl;
}