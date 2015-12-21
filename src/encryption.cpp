#include <climits>

#include "encryption.hpp"
#include "encoding.hpp"
#include "conversions.hpp"
#include "analysis.hpp"
#include "utils.hpp"


std::vector<uint8_t> repeated_xor(const std::vector<uint8_t>& key, const std::vector<uint8_t>& msg)
{
    auto expanded_key = expand_key_to_length(key, msg.size());

    std::vector<unsigned char> bin;
    bin.reserve(msg.size());

    for (size_t i = 0; i < msg.size(); ++i) {
        auto c = static_cast<unsigned char>(msg[i] ^ expanded_key[i]);
        bin.push_back(c);
    }

    return bin;
}

std::vector<uint8_t> repeated_xor_break(const std::vector<uint8_t>& encrypted)
{
    decltype(repeated_xor_break(encrypted)) result;

    std::tuple<long, char> key_length{ LONG_MAX, 0 };

    for (char i = 1; i < 41; ++i) {
        std::vector<uint8_t> first(encrypted.begin(), encrypted.begin() + i);
        std::vector<uint8_t> second(encrypted.begin() + i, encrypted.begin() + i * 2);
        std::vector<uint8_t> third(encrypted.begin() + i * 2, encrypted.begin() + i * 3);

        auto distance = (hamming_distance(first, second) + hamming_distance(second, third)) / 2;
        if (distance < std::get<0>(key_length)) {
            key_length = std::make_tuple(distance, i);
        }
    }

    return result;
}

std::tuple<long, std::string> single_byte_xor_cipher(const std::vector<uint8_t>& msg)
{
    std::tuple<long, std::string> answer{ 0, "" };

    for (auto i = 0; i <= 0xff; ++i) {
        std::vector<uint8_t> key{ static_cast<uint8_t>(i) };

        auto decoded = bytes_to_string(repeated_xor(key, msg));

        auto score = scorer(decoded);

        if (score > std::get<0>(answer)) {
            answer = std::make_tuple(score, decoded);
        }
    }

    return answer;
}

std::tuple<long, std::string, std::string> single_byte_xor_cipher_from_list(const std::vector<std::string>& list)
{
    std::tuple<long, std::string, std::string> result{ 0, "", "" };

    for (const auto& v : list) {
        auto candidate = single_byte_xor_cipher(hex_to_bytes(v));

        if (std::get<0>(candidate) > std::get<0>(result)) {
            result = std::make_tuple(std::get<0>(candidate), std::get<1>(candidate), v);
        }
    }

    return result;
}