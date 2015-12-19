#include "encoding.hpp"

namespace {

    const std::string BASE64_MAP = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    char first(uint8_t(&octets)[3])
    {
        return BASE64_MAP[octets[0] >> 2];
    }

    char second(uint8_t(&octets)[3])
    {
        return BASE64_MAP[((octets[0] & 0x3) << 4) + (octets[1] >> 4)];
    }

    char third(uint8_t(&octets)[3])
    {
        return BASE64_MAP[((octets[1] & 0xf) << 2) + (octets[2] >> 6)];
    }

    char fourth(uint8_t(&octets)[3])
    {
        return BASE64_MAP[octets[2] & 0x3f];
    }

}

std::string base64_encode(const std::vector<uint8_t>& input)
{
    std::string result;
    result.reserve(input.size() / 3 * 4);

    uint8_t octets[3];

    for (decltype(input.size()) i = 0; i + 2 < input.size(); i += 3) {
        octets[0] = input.at(i);
        octets[1] = input.at(i + 1);
        octets[2] = input.at(i + 2);

        result.push_back(first(octets));
        result.push_back(second(octets));
        result.push_back(third(octets));
        result.push_back(fourth(octets));
    }

    auto remainder = input.size() % 3;
    if (remainder > 0) {
        octets[0] = octets[1] = octets[2] = 0;

        auto last = input.end();
        for (auto i = remainder; i > 0; --i) {
            octets[i - 1] = *(--last);
        }

        result.push_back(first(octets));
        result.push_back(second(octets));

        if (remainder == 2) {
            result.push_back(third(octets));
        }

        std::string padding(3 - remainder, '=');
        result.append(padding);
    }

    return result;
}