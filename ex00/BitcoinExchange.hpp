#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>


class BitcoinExchange
{
    private:
        std::map<std::string, double> exchangeRates;
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();
        void run(const std::string& filename);
        void parse_data_file(const std::string& filename);
        void parse_input_file(const std::string& filename);
        void print_exchange_rate(const std::string& date, double value) const;

};

std::string trim(const std::string& str);

#endif