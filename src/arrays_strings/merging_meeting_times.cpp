#include <iostream>
#include <vector>

// C++11 lest unit testing framework
#include "lest.hpp"

using namespace std;

class Meeting {
private:
    // number of 30 min blocks past 9:00 am
    unsigned int startTime_;
    unsigned int endTime_;

public:
    Meeting()
        : startTime_(0)
        , endTime_(0)
    {
    }

    Meeting(unsigned int startTime, unsigned int endTime)
        : startTime_(startTime)
        , endTime_(endTime)
    {
    }

    unsigned int getStartTime() const
    {
        return startTime_;
    }

    void setStartTime(unsigned int startTime)
    {
        startTime_ = startTime;
    }

    unsigned int getEndTime() const
    {
        return endTime_;
    }

    void setEndTime(unsigned int endTime)
    {
        endTime_ = endTime;
    }

    bool operator==(const Meeting& other) const
    {
        return startTime_ == other.startTime_
            && endTime_ == other.endTime_;
    }
};

vector<Meeting> mergeMeetings(vector<Meeting> left,
    vector<Meeting> right)
{
    vector<Meeting> mergedMeetings;

    // Pick compare the head element of left to right, and push_back the lowest
    while (!left.empty() && !right.empty()) {
        if (left.front().getStartTime() < right.front().getStartTime()) {
            mergedMeetings.push_back(left.front());
            left.erase(left.begin());
        } else {
            mergedMeetings.push_back(right.front());
            right.erase(right.begin());
        }
    }

    // Only one of these should execute
    if (!left.empty()) {
        mergedMeetings.insert(mergedMeetings.end(), begin(left), end(left));
    }
    if (!right.empty()) {
        mergedMeetings.insert(mergedMeetings.end(), begin(right), end(right));
    }

    return mergedMeetings;
}

vector<Meeting> sortMeetings(const vector<Meeting>& meetings)
{
    vector<Meeting> sortedMeetings;

    // Base case single meeting
    if (meetings.size() == 1) {
        sortedMeetings = meetings; // Sorted, by definition
    }

    // Divide the vector and combine the results
    else {
        unsigned int split_index = meetings.size() / 2;

        vector<Meeting> l(meetings.begin(), meetings.begin() + split_index);
        vector<Meeting> r(meetings.begin() + split_index, meetings.end());

        // Recursive call to build out tree to single leaf nodes
        vector<Meeting> sortedLeft = sortMeetings(l);
        vector<Meeting> sortedRight = sortMeetings(r);

        // On return up the tree, merge each sorted subset
        sortedMeetings = mergeMeetings(sortedLeft, sortedRight);
    }

    return sortedMeetings;
}

vector<Meeting> combineMeetings(const vector<Meeting>& meetings)
{
    vector<Meeting> combinedMeetings;
    combinedMeetings.push_back(meetings.front());

    for (const Meeting& m : meetings) {
        // Reference the last merged meeting
        Meeting& l = combinedMeetings.back();

        // Combine overlapping meetingss
        if (l.getEndTime() >= m.getStartTime()) {
            unsigned int et = max(l.getEndTime(),
                m.getEndTime());
            l.setEndTime(et);
        }

        // No overlap
        else {
            combinedMeetings.push_back(m);
        }
    }

    return combinedMeetings;
}

vector<Meeting> mergeRanges(const vector<Meeting>& meetings)
{
    vector<Meeting> sortedMeetings = sortMeetings(meetings); // O(n*lg(n))
    vector<Meeting> combinedMeetings = combineMeetings(sortedMeetings); // O(n)
    return combinedMeetings;
}

// tests
const lest::test tests[] = {
    {CASE("meetings overlap") {
        const auto meetings = vector<Meeting> {Meeting(1, 3), Meeting(2, 4)};
        const auto actual = mergeRanges(meetings);
        const auto expected = vector<Meeting> {Meeting(1, 4)};
        EXPECT(actual == expected);
    }},

    {CASE("meetings touch") {
        const auto meetings = vector<Meeting> {Meeting(5, 6), Meeting(6, 8)};
        const auto actual = mergeRanges(meetings);
        const auto expected = vector<Meeting> {Meeting(5, 8)};
        EXPECT(actual == expected);
    }},

    {CASE("meeting contains other meeting") {
        const auto meetings = vector<Meeting> {Meeting(1, 8), Meeting(2, 5)};
        const auto actual = mergeRanges(meetings);
        const auto expected = vector<Meeting> {Meeting(1, 8)};
        EXPECT(actual == expected);
    }},

    {CASE("meetings stay separate") {
        const auto meetings = vector<Meeting> {Meeting(1, 3), Meeting(4, 8)};
        const auto actual = mergeRanges(meetings);
        const auto expected = vector<Meeting> {Meeting(1, 3), Meeting(4, 8)};
        EXPECT(actual == expected);
    }},

    {CASE("multiple merged meetings") {
        const auto meetings = vector<Meeting> {Meeting(1, 4), Meeting(2, 5), Meeting(5, 8)};
        const auto actual = mergeRanges(meetings);
        const auto expected = vector<Meeting> {Meeting(1, 8)};
        EXPECT(actual == expected);
    }},

    {CASE("meetings not sorted") {
        const auto meetings = vector<Meeting> {Meeting(5, 8), Meeting(1, 4), Meeting(6, 8)};
        const auto actual = mergeRanges(meetings);
        const auto expected = vector<Meeting> {Meeting(1, 4), Meeting(5, 8)};
        EXPECT(actual == expected);
    }},

    {CASE("one long meeting contains smaller meetings") {
        const auto meetings = vector<Meeting> {Meeting(1, 10), Meeting(2, 5), Meeting(6, 8),
            Meeting(9, 10), Meeting(10, 12)};
        const auto actual = mergeRanges(meetings);
        const auto expected = vector<Meeting> {Meeting(1, 12)};
        EXPECT(actual == expected);
    }},

    {CASE("sample input") {
        const auto meetings = vector<Meeting> {Meeting(0, 1), Meeting(3, 5), Meeting(4, 8),
            Meeting(10, 12), Meeting(9, 10)};
        const auto actual = mergeRanges(meetings);
        const auto expected = vector<Meeting> {Meeting(0, 1), Meeting(3, 8), Meeting(9, 12)};
        EXPECT(actual == expected);
    }},
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
