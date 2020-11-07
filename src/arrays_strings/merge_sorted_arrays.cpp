#include <iostream>
#include <vector>

// C++11 lest unit testing framework
#include "lest.hpp"

using namespace std;

vector<int> mergeVectors(const vector<int>& myVector, const vector<int>& alicesVector)
{
    // Combine the sorted vectors into one large sorted vector
    vector<int> mergedVector(myVector.size() + alicesVector.size());
    size_t il = 0;  // index left
    size_t ir = 0;  // index right
    size_t im = 0;  // index merged

    while(im < mergedVector.size()) {
        bool myVectorIsEmpty = il >= myVector.size();
        bool alicesVectorIsEmpty = ir >= alicesVector.size();

        if (!myVectorIsEmpty && !alicesVectorIsEmpty) {
            // Compare the pre-sorted vectors and merge the lower value first
            if (myVector[il] <= alicesVector[ir]) {
                mergedVector[im++] = myVector[il++];
            } else {
                mergedVector[im++] = alicesVector[ir++];
            }
        } else {
            // Fill in the remaining from the non-empty vector
            if (myVectorIsEmpty) mergedVector[im++] = alicesVector[ir++];
            if (alicesVectorIsEmpty) mergedVector[im++] = myVector[il++];
        }
    }

    return mergedVector;
}

// tests

const lest::test tests[] = {
    {CASE("both vectors are empty") {
        const vector<int> myVector;
        const vector<int> alicesVector;
        const vector<int> expected;
        const auto actual = mergeVectors(myVector, alicesVector);
        EXPECT(actual == expected);
    }},
    {CASE("first vector is empty") {
        const vector<int> myVector;
        const vector<int> alicesVector {1, 2, 3};
        const vector<int> expected {1, 2, 3};
        const auto actual = mergeVectors(myVector, alicesVector);
        EXPECT(actual == expected);
    }},
    {CASE("second vector is empty") {
        const vector<int> myVector {5, 6, 7};
        const vector<int> alicesVector;
        const vector<int> expected {5, 6, 7};
        const auto actual = mergeVectors(myVector, alicesVector);
        EXPECT(actual == expected);
    }},
    {CASE("both vectors have some numbers") {
        const vector<int> myVector {2, 4, 6};
        const vector<int> alicesVector {1, 3, 7};
        const vector<int> expected {1, 2, 3, 4, 6, 7};
        const auto actual = mergeVectors(myVector, alicesVector);
        EXPECT(actual == expected);
    }},
    {CASE("vectors are different lengths") {
        const vector<int> myVector {2, 4, 6, 8};
        const vector<int> alicesVector {1, 7};
        const vector<int> expected {1, 2, 4, 6, 7, 8};
        const auto actual = mergeVectors(myVector, alicesVector);
        EXPECT(actual == expected);
    }}
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
