#pragma once

#include <string>
#include <vector>

#include "export.hpp"

DllExport std::vector<uint8_t> hex_to_bytes(const std::string&);
DllExport std::vector<uint8_t> string_to_bytes(const std::string&);
DllExport std::string bytes_to_hex(const std::vector<uint8_t>&);
std::string bytes_to_string(const std::vector<uint8_t>&);