#include "conversions.hpp"

namespace {

    uint8_t hex_to_number(const char c)
    {
        if ('0' <= c && c <= '9') {
            return c - '0';
        }

        if ('A' <= c && c <= 'Z') {
            return c - 'A' + 10;
        }

        return c - 'a' + 10;
    }

    uint8_t pair_to_byte(const char a, const char b)
    {
        return (hex_to_number(a) << 4) + hex_to_number(b);
    }

    char byte_to_hex(const char c)
    {
        if (c < 10) {
            return '0' + c;
        }

        return 'a' + c - 10;
    }

}



std::vector<uint8_t> hex_to_bytes(const std::string& str)
{
    std::vector<uint8_t> bytes;
    bytes.reserve(str.size() / 2);

    for (size_t i = 0; i < str.size(); i += 2) {
        bytes.push_back(pair_to_byte(str[i], str[i + 1]));
    }

    return bytes;
}

std::vector<uint8_t> string_to_bytes(const std::string& str)
{
    return std::vector<uint8_t>(str.begin(), str.end());
}

std::string bytes_to_hex(const std::vector<uint8_t>& input)
{
    std::string result;
    result.reserve(input.size() * 2);

    for (auto c : input) {
        char high = c >> 4;
        char low = c & 0xf;

        result.push_back(byte_to_hex(high));
        result.push_back(byte_to_hex(low));
    }

    return result;
}

std::string bytes_to_string(const std::vector<uint8_t>& input)
{
    return std::string(input.begin(), input.end());
}

uint8_t base64_char_to_value(const char c)
{
    if ('A' <= c && c <= 'Z') {
        return c - 'A';
    }

    if ('a' <= c && c <= 'z') {
        return c - 'a' + 26;
    }

    if ('0' <= c && c <= '9') {
        return c - '0' + 52;
    }

    switch (c) {
    case '+':
        return 62; break;
    case '/':
        return 63; break;
    }

    return 64;
}