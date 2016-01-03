#pragma once

#include <string>
#include <vector>
#include <tuple>

#include "export.hpp"

DllExport std::vector<uint8_t> repeated_xor(const std::vector<uint8_t>&, const std::vector<uint8_t>&);
DllExport std::vector<uint8_t> repeated_xor_break(const std::vector<uint8_t>&, int max_key_length, int max_keys_check);

DllExport std::tuple<long, std::string> single_byte_xor_cipher(const std::vector<uint8_t>&);
DllExport std::tuple<long, std::string, std::string> single_byte_xor_cipher_from_list(const std::vector<std::string>& list);