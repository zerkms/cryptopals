#pragma once

#include <string>
#include <vector>
#include <tuple>

std::vector<uint8_t> repeated_xor(const std::vector<uint8_t>&, const std::vector<uint8_t>&);

std::tuple<long, std::string> single_byte_xor_cipher(const std::string&);
std::tuple<long, std::string, std::string> single_byte_xor_cipher_from_list(const std::vector<std::string>& list);