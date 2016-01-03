#pragma once

#include <string>
#include <vector>

#include "export.hpp"

long scorer(const std::string& str);
DllExport long hamming_distance(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b);
DllExport double weighted_hamming_distance(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b);