#include <climits>
#include <queue>

#include "encryption.hpp"
#include "encoding.hpp"
#include "conversions.hpp"
#include "analysis.hpp"
#include "utils.hpp"

using key_distance_t = std::tuple<double, char>;

namespace {

    auto find_key_length(const std::vector<uint8_t>& encrypted, int max_key_length)
    {
        auto key_distance_comp = [](const key_distance_t& a, const key_distance_t& b) {
            return std::get<0>(a) > std::get<0>(b);
        };

        std::priority_queue<key_distance_t, std::vector<key_distance_t>, decltype(key_distance_comp)> key_distance_queue(key_distance_comp);

        key_distance_t key_and_distance{ LONG_MAX, 0 };

        for (char i = 1; i < max_key_length; ++i) {
            std::vector<uint8_t> first(encrypted.begin(), encrypted.begin() + i);
            std::vector<uint8_t> second(encrypted.begin() + i, encrypted.begin() + i * 2);
            std::vector<uint8_t> third(encrypted.begin() + i * 2, encrypted.begin() + i * 3);

            auto distance = (weighted_hamming_distance(first, second) + weighted_hamming_distance(second, third)) / 2;
            key_distance_queue.push(std::make_tuple(distance, i));
        }

        return key_distance_queue;
    }

    auto multi_byte_xor_cipher(const std::vector<uint8_t>& encrypted, char key_length)
    {
        std::vector<uint8_t> result(encrypted.size());

        long score_sum = 0;
        for (char i = 0; i < key_length; ++i) {
            decltype(result) slice;
            slice.reserve(encrypted.size() / key_length + key_length);

            for (decltype(slice)::size_type j = i; j < encrypted.size(); j += key_length) {
                slice.push_back(encrypted[j]);
            }

            auto decrypted_with_score = single_byte_xor_cipher(slice);
            score_sum += std::get<0>(decrypted_with_score);
            auto decrypted = std::get<1>(decrypted_with_score);

            for (decltype(result)::size_type j = 0; j < decrypted.size(); ++j) {
                result[j * key_length + i] = decrypted[j];
            }
        }

        return std::make_tuple(score_sum, result);
    }

}

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

std::vector<uint8_t> repeated_xor_break(const std::vector<uint8_t>& encrypted, int max_key_length, int max_keys_check)
{
    auto key_distance_queue = find_key_length(encrypted, max_key_length);

    std::tuple<long, std::vector<uint8_t>> highest_scored_result{ 0, std::vector<uint8_t>() };

    for (decltype(max_keys_check) i = 0; i < max_keys_check && !key_distance_queue.empty(); ++i) {
        auto key_distance = key_distance_queue.top();
        key_distance_queue.pop();

        auto key_length = std::get<1>(key_distance);
        auto candidate = multi_byte_xor_cipher(encrypted, key_length);

        if (candidate > highest_scored_result) {
            highest_scored_result = candidate;
        }
    }

    return std::get<1>(highest_scored_result);
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