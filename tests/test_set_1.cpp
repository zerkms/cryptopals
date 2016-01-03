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

    auto actual = single_byte_xor_cipher(hex_to_bytes(msg));

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

TEST_CASE("S1C6", "[S1]") {
    std::string expected{ "I'm back and I'm ringin' the bell \nA rockin' on the mike while the fly girls yell \nIn ecstasy in the back of me \nWell that's my DJ Deshay cuttin' all them Z's \nHittin' hard and the girlies goin' crazy \nVanilla's on the mike, man I'm not lazy. \n\nI'm lettin' my drug kick in \nIt controls my mouth and I begin \nTo just let it flow, let my concepts go \nMy posse's to the side yellin', Go Vanilla Go! \n\nSmooth 'cause that's the way I will be \nAnd if you don't give a damn, then \nWhy you starin' at me \nSo get off 'cause I control the stage \nThere's no dissin' allowed \nI'm in my own phase \nThe girlies sa y they love me and that is ok \nAnd I can dance better than any kid n' play \n\nStage 2 -- Yea the one ya' wanna listen to \nIt's off my head so let the beat play through \nSo I can funk it up and make it sound good \n1-2-3 Yo -- Knock on some wood \nFor good luck, I like my rhymes atrocious \nSupercalafragilisticexpialidocious \nI'm an effect and that you can bet \nI can take a fly girl and make her wet. \n\nI'm like Samson -- Samson to Delilah \nThere's no denyin', You can try to hang \nBut you'll keep tryin' to get my style \nOver and over, practice makes perfect \nBut not if you're a loafer. \n\nYou'll get nowhere, no place, no time, no girls \nSoon -- Oh my God, homebody, you probably eat \nSpaghetti with a spoon! Come on and say it! \n\nVIP. Vanilla Ice yep, yep, I'm comin' hard like a rhino \nIntoxicating so you stagger like a wino \nSo punks stop trying and girl stop cryin' \nVanilla Ice is sellin' and you people are buyin' \n'Cause why the freaks are jockin' like Crazy Glue \nMovin' and groovin' trying to sing along \nAll through the ghetto groovin' this here song \nNow you're amazed by the VIP posse. \n\nSteppin' so hard like a German Nazi \nStartled by the bases hittin' ground \nThere's no trippin' on mine, I'm just gettin' down \nSparkamatic, I'm hangin' tight like a fanatic \nYou trapped me once and I thought that \nYou might have it \nSo step down and lend me your ear \n'89 in my time! You, '90 is my year. \n\nYou're weakenin' fast, YO! and I can tell it \nYour body's gettin' hot, so, so I can smell it \nSo don't be mad and don't be sad \n'Cause the lyrics belong to ICE, You can call me Dad \nYou're pitchin' a fit, so step back and endure \nLet the witch doctor, Ice, do the dance to cure \nSo come up close and don't be square \nYou wanna battle me -- Anytime, anywhere \n\nYou thought that I was weak, Boy, you're dead wrong \nSo come on, everybody and sing this song \n\nSay -- Play that funky music Say, go white boy, go white boy go \nplay that funky music Go white boy, go white boy, go \nLay down and boogie and play that funky music till you die. \n\nPlay that funky music Come on, Come on, let me hear \nPlay that funky music white boy you say it, say it \nPlay that funky music A little louder now \nPlay that funky music, white boy Come on, Come on, Come on \nPlay that funky music \n" };

    std::ifstream file{ "6.txt" };
    std::string encrypted;

    for (std::string line; std::getline(file, line);) {
        encrypted.append(line);
    }

    auto actual = bytes_to_string(repeated_xor_break(base64_decode(encrypted), 41, 10));

    REQUIRE(actual == expected);
}