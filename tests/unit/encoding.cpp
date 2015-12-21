#include "catch.hpp"

#include "encoding.hpp"
#include "conversions.hpp"

TEST_CASE("base64_decode", "[UNIT][encoding]") {

    std::string expected{ "Hello World!" };
    std::string input{ "SGVsbG8gV29ybGQh" };

    auto actual = bytes_to_string(base64_decode(input));

    REQUIRE(actual == expected);

}