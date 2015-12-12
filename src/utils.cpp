#include <vector>

#include "utils.hpp"

std::vector<uint8_t> expand_key_to_length(const std::vector<uint8_t>& base, std::vector<uint8_t>::size_type length)
{
    std::vector<uint8_t> result(length);

    auto base_length = base.size();
    for (decltype(length) i = 0; i < length; ++i) {
        result[i] = base[i % base_length];
    }

    return result;
}