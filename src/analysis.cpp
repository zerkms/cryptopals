#include "analysis.hpp"

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