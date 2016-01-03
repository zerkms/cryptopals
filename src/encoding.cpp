#include "encoding.hpp"
#include "conversions.hpp"

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
    result.reserve(input.size() / 3 * 4 + 4);

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

std::vector<uint8_t> base64_decode(const std::string& msg)
{
    decltype(base64_decode("")) result;
    result.reserve(msg.length() / 4 * 3 + 3);

    uint8_t chars[4];

    for (size_t i = 0; i < msg.size(); i += 4) {
        chars[0] = base64_char_to_value(msg[i]);
        chars[1] = base64_char_to_value(msg[i + 1]);
        chars[2] = base64_char_to_value(msg[i + 2]);
        chars[3] = base64_char_to_value(msg[i + 3]);

        unsigned char octet = (chars[0] << 2) + ((chars[1] & 0x30) >> 4);
        result.push_back(octet);

        if (msg[i + 2] == '=') {
            break;
        }

        octet = ((chars[1] & 0xf) << 4) + ((chars[2] & 0x3c) >> 2);
        result.push_back(octet);

        if (msg[i + 3] == '=') {
            break;
        }

        octet = ((chars[2] & 0x3) << 6) + (chars[3] & 0x3f);
        result.push_back(octet);
    }

    return result;
}