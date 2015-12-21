#include "analysis.hpp"

namespace {
    char bits_set_count(uint8_t c)
    {
        char count = 0;

        while (c > 0) {
            if ((c & 1) == 1) {
                ++count;
            }

            c >>= 1;
        }

        return count;
    }
}

long scorer(const std::string& str)
{
    auto score = 0L;
    for (auto c : str) {

        switch (c) {
        case 'E':
        case 'e':
            score += 13; break;

        case 'T':
        case 't':
            score += 12; break;

        case 'A':
        case 'a':
            score += 11; break;

        case 'O':
        case 'o':
            score += 10; break;

        case 'I':
        case 'i':
            score += 9; break;

        case 'N':
        case 'n':
            score += 8; break;

        case ' ':
            score += 7; break;

        case 'S':
        case 's':
            score += 6; break;

        case 'H':
        case 'h':
            score += 5; break;

        case 'R':
        case 'r':
            score += 4; break;

        case 'D':
        case 'd':
            score += 3; break;

        case 'L':
        case 'l':
            score += 2; break;

        case 'U':
        case 'u':
            score += 1; break;
        }
    }

    return score;
}

long hamming_distance(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b)
{
    int distance = 0L;

    for (size_t i = 0; i < a.size(); ++i) {
        unsigned char x = a[i] ^ b[i];
        distance += bits_set_count(x);
    }

    return distance;
}