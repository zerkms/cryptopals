#pragma once

#include <string>
#include <vector>

std::vector<uint8_t> hex_to_bytes(const std::string&);
std::vector<uint8_t> string_to_bytes(const std::string&);
std::string bytes_to_hex(const std::vector<uint8_t>&);
std::string bytes_to_string(const std::vector<uint8_t>&);