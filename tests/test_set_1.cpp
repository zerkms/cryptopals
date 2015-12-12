#include "catch.hpp"

#include <iostream>
#include <iterator>
#include <fstream>

#include "encryption.hpp"
#include "conversions.hpp"
#include "encoding.hpp"

TEST_CASE("S1C1", "[S1]") {
    std::string input{ "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d" };
    std::string expected{ "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t" };

    auto actual = base64_encode(hex_to_bytes(input));

    REQUIRE(actual == expected );
}

TEST_CASE("S1C2", "[S1]") {
    std::string a{ "1c0111001f010100061a024b53535009181c" };
    std::string b{ "686974207468652062756c6c277320657965" };
    std::string expected{ "746865206b696420646f6e277420706c6179" };

    auto actual = bytes_to_hex(repeated_xor(hex_to_bytes(a), hex_to_bytes(b)));

    REQUIRE(actual == expected);
}

TEST_CASE("S1C3", "[S1]") {
    std::string msg{ "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736" };
    std::string expected{ "Cooking MC's like a pound of bacon" };

    auto actual = single_byte_xor_cipher(msg);

    REQUIRE(std::get<1>(actual) == expected);
}

TEST_CASE("S1C4", "[S1]") {
    std::string expected{ "Now that the party is jumping\n" };

    std::ifstream file{ "4.txt" };
    std::vector<std::string> lines;

    std::copy(
        std::istream_iterator<std::string>(file),
        std::istream_iterator<std::string>(),
        std::back_inserter(lines)
        );

    auto actual = single_byte_xor_cipher_from_list(lines);

    REQUIRE(std::get<1>(actual) == expected);
}

TEST_CASE("S1C5", "[S1]") {
    std::string expected{ "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f" };

    std::string msg{ "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal" };
    std::string key{ "ICE" };

    auto actual = bytes_to_hex(repeated_xor(string_to_bytes(key), string_to_bytes(msg)));

    REQUIRE(actual == expected);
}