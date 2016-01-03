#include "catch.hpp"

#include "analysis.hpp"
#include "conversions.hpp"

TEST_CASE("wokka", "[UNIT][analysis]") {

    std::string a{ "this is a test" };
    std::string b{ "wokka wokka!!!" };

    auto expected = 37L;
    auto actual = hamming_distance(string_to_bytes(a), string_to_bytes(b));

    REQUIRE(actual == expected);

}

TEST_CASE("weighted wokka", "[UNIT][analysis]") {

    std::string a{ "this is a test" };
    std::string b{ "wokka wokka!!!" };

    auto expected = 2.6428571429;
    auto actual = weighted_hamming_distance(string_to_bytes(a), string_to_bytes(b));

    REQUIRE(actual == Approx(expected));

}