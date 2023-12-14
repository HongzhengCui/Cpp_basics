#ifndef PARSE_HPP
#define PARSE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<std::string> split_line(const std::string& line);

void read_universe(const std::string& filename,
                   std::vector<std::string>& asset_name,
                   std::vector<double>& average_rate_of_return,
                   std::vector<double>& standard_deviation);

void read_correlation(const std::string& filename,
                      std::vector<std::vector<double>>& correlation_vectors);

#endif
