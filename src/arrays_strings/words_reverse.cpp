#include <iostream>
#include <string>

// C++11 lest unit testing framework
#include "lest.hpp"

using namespace std;

void reverseWords(string& message)
{
    string word;

    // Return early if only given a single word
    if (find(begin(message), end(message), ' ') == end(message)) {
        return;
    }

    // Reverse the entire message
    reverse(begin(message), end(message));

    // Iterate over each word in the message, including the last one, and reverse it
    uint word_begin = 0;
    for (uint i = 0; i <= message.length(); i++) {
        // Short-circuit OR avoids deref '/0' termination with std::string::at(i)
        if (i == message.length() || message.at(i) == ' ') {
            reverse(begin(message) + word_begin, begin(message) + i);
            word_begin = i + 1;
        }
    }
}

// tests

const lest::test tests[] = {
    {CASE("one word") {
        const string expected = "vault";
        string actual = "vault";
        reverseWords(actual);
        EXPECT(actual == expected);
    }},
    {CASE("two words") {
        const string expected = "cake thief";
        string actual = "thief cake";
        reverseWords(actual);
        EXPECT(actual == expected);
    }},
    {CASE("three words") {
        const string expected = "get another one";
        string actual = "one another get";
        reverseWords(actual);
        EXPECT(actual == expected);
    }},
    {CASE("multiple words same length") {
        const string expected = "the cat ate the rat";
        string actual = "rat the ate cat the";
        reverseWords(actual);
        EXPECT(actual == expected);
    }},
    {CASE("multiple words different lengths") {
        const string expected = "chocolate bundt cake is yummy";
        string actual = "yummy is cake bundt chocolate";
        reverseWords(actual);
        EXPECT(actual == expected);
    }},
    {CASE("empty string") {
        const string expected;
        string actual;
        reverseWords(actual);
        EXPECT(actual == expected);
    }}
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
