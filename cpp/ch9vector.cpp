// Example from MSDN Ch9 Lecture on C++ STL
// Sort a vector

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


// Sort a vector of int
void Example1(void)
{
    cout << "--- " << __FUNCTION__ << endl;

    vector<int> v;

    v.push_back(44);
    v.push_back(11);
    v.push_back(33);
    v.push_back(55);
    v.push_back(22);

    //for (vector<int>::iterator i = v.begin(); i != v.end(); ++i) {
    for (auto i : v) {
        cout << i << endl;
    }

    cout << "--- Sort ascending" << endl;
    sort(v.begin(), v.end());

    //for (vector<int>::iterator i = v.begin(); i != v.end(); ++i) {
    for (auto i : v) {
        cout << i << endl;
    }

    v.clear();
}


// Sort a vector of string
void Example2(void)
{
    cout << "--- " << __FUNCTION__ << endl;

    vector<string> v;

    v.push_back("dog");
    v.push_back("antelope");
    v.push_back("bear");
    v.push_back("zebra");
    v.push_back("kitten");

    //for (vector<string>::iterator i = v.begin(); i != v.end(); ++i) {
    for (auto i : v) {
        cout << i << endl;
    }

    cout << "--- Sort lexicographically" << endl;
    sort(v.begin(), v.end());

    //for (vector<string>::iterator i = v.begin(); i != v.end(); ++i) {
    for (auto i : v) {
        cout << i << endl;
    }

    v.clear();
}

// a vector of string, sort with functor
//template<typename T>
class compare_length {
    public:
    // more can be done in this class
    // for example, collect statistics about the number of times called
    // or counts strings or total length, etc.
    bool operator()(const string& left, const string& right) {
        return left.size() < right.size();
    }
};

void Example3(void)
{
    cout << "--- " << __FUNCTION__ << endl;

    vector<string> v;
    v.push_back("dog");
    v.push_back("antelope");
    v.push_back("bear");
    v.push_back("zebra");
    v.push_back("kitten");

    // for (vector<string>::iterator i = v.begin(); i != v.end(); ++i) {
    for (auto i : v) {
        cout << i << endl;
    }

    cout << "--- Sort by length" << endl;
    sort(v.begin(), v.end(), compare_length());

    //for (vector<string>::iterator i = v.begin(); i != v.end(); ++i) {
    for (auto i : v) {
        cout << i << endl;
    }

    v.clear();
}

// a vector of string, sort with function
bool cmp_len(const string& left, const string& right)
{
    return left.size() < right.size();
}

void Example4(void)
{
    cout << "--- " << __FUNCTION__ << endl;

    vector<string> v;
    v.push_back("apple");
    v.push_back("blueberry");
    v.push_back("cherry");
    v.push_back("date");
    v.push_back("elderberry");

    for (auto i : v) {
        cout << i << endl;
    }

    cout << "--- Sort by length" << endl;
    sort(v.begin(), v.end(), cmp_len);

    for (auto i : v) {
        cout << i << endl;
    }

    v.clear();
}


int main()
{
    Example1();
    Example2();
    Example3();
    Example4();
    return 0;
}
