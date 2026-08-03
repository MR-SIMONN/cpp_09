#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
    exchangeRates = other.exchangeRates;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    exchangeRates = other.exchangeRates;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}


bool is_number(const std::string& value)
{
	size_t i = 0;
	int dot = 0;
	bool has_digit = false;
	
	if (value.empty())
		return (false);
	if (value[0] == '-')
		i++;
	while (i < value.length())
	{
		if (!isdigit(value[i]) && value[i] != '.')
			return (false);
		if (isdigit(value[i]))
			has_digit = true;
		if (dot == 1 && !isdigit(value[i]))
			return (false);
		if (value[i] == '.')
				dot++;
		i++;
	}
	return (has_digit);
}


std::string trim(const std::string& str)
{
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    return (first == std::string::npos ? "" : str.substr(first, last - first + 1));
}


bool valid_date(const std::string& date)
{
	// Check if the date is in the format YYYY-MM-DD
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	for (int i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(date[i]))
			return false;
	}

	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31)
		return false;

	bool LeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	int month_days[] = { 31, (LeapYear ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (day > month_days[month - 1])
		return false;

	return (true);
}

bool valid_value(const std::string& value_str)
{
	if (!is_number(value_str))
	{
		std::cout << "Error: Invalid value." << std::endl;
		return (false);
	}
	double value = std::atof(value_str.c_str());
	if (value < 0)
	{
		std::cout << "Error: not a positive number." << std::endl;
		return (false);
	}
	if (value > 1000)
	{
		std::cout << "Error: too large a number." << std::endl;
		return (false);
	}

	return (true);
}

bool valid_date_and_value(const std::string& date, const std::string& value)
{
	if (!valid_date(date))
	{
		std::cout << "Error: Invalid date." << std::endl;
		return false;
	}
	if (!valid_value(value))
	{
		std::cout << "Error: Invalid value." << std::endl;
		return false;
	}
	return true;
}


void BitcoinExchange::print_exchange_rate(const std::string& date, double value) const
{
	std::map<std::string, double>::const_iterator it = exchangeRates.lower_bound(date);
	if (it != exchangeRates.end() && it->first == date)
		std::cout << date << " => " << value << " = " << it->second * value << std::endl;
	else if (it == exchangeRates.begin() && it->first != date)
		std::cout << "Error: Date not found." << std::endl;
	else
	{
		--it;
		std::cout << date << " => " << value << " = " << it->second * value << std::endl;
	}
}


// date and value format : YYYY-MM-DD,<value>

void BitcoinExchange::parse_data_file(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cout << "Error: Could not open data file." << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Skip the header line
    while (std::getline(file, line))
    {
        size_t commaPos = line.find(',');
        if (commaPos != std::string::npos)
        {
            std::string date = trim(line.substr(0, commaPos));
            std::string value_str = trim(line.substr(commaPos + 1));
            double value = std::atof(value_str.c_str());
			// if (valid_date_and_value(date, value_str))
            	exchangeRates[date] = value;
        }
    }
    file.close();
}

void BitcoinExchange::parse_input_file(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cout << "Error: Could not open input file." << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Skip the header line
    while (std::getline(file, line))
    {
        size_t commaPos = line.find('|');
        if (commaPos != std::string::npos)
        {
            std::string date = trim(line.substr(0, commaPos));
            std::string value = trim(line.substr(commaPos + 1));
            if (valid_date_and_value(date, value))
                print_exchange_rate(date, std::atof(value.c_str()));
        }
    }
    file.close();
}

void BitcoinExchange::run(const std::string& input_filename)
{
    parse_data_file("data.csv");
    parse_input_file(input_filename);
}