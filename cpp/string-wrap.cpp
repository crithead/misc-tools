// string-wrap
// Wrap a string on spaces.

#include <cassert>
#include <exception>
#include <fstream>
#include <iostream>
#include <list>
#include <string>

using namespace std;

static void stars(size_t);
static void test1(void);
static void test2(void);
static void test3(void);
static void test4(void);
static void test5(void);
static list<string> wrap(const string&, size_t);
static void wrap_file(const char *);

int main(int argc, char **argv)
{
    if (argc > 1) {
        for (int i = 1; i < argc; i++)
            wrap_file(argv[i]);
    } else {
        test1();
        test2();
        test3();
        test4();
        test5();
    }
}

void stars(size_t len)
{
    for (size_t i = 0 ; i < len; i++)
        cout << '*';
    cout << endl;
}

void test1(void)
{
    const size_t len = 20;
    const string s1 = string("Row, row, row, your boat."
            " Gently down the stream. Merrily, merrily, merrily."
            " Life is but a dream.");
    list<string> lines = wrap(s1, len);
    stars(len);
    for (auto line : lines)
        cout << line << endl;
}

void test2(void)
{
    const size_t len = 40;
    const string s1 = string(
            "abcdefghijklmnopqrstuvwxyz" "abcdefghijklmnopqrstuvwxyz"
            "abcdefghijklmnopqrstuvwxyz" "abcdefghijklmnopqrstuvwxyz"
            "abcdefghijklmnopqrstuvwxyz" "abcdefghijklmnopqrstuvwxyz"
            "abcdefghijklmnopqrstuvwxyz" "abcdefghijklmnopqrstuvwxyz"
            "abcdefghijklmnopqrstuvwxyz" "abcdefghijklmnopqrstuvwxyz");
    list<string> lines = wrap(s1, len);
    stars(len);
    for (auto line : lines)
        cout << line << endl;
}

void test3(void)
{
    const size_t len = 52;
    const string s1 = string(
        "You see a woman carrying a baby and loudly remark how ugly it is."
    );

    list<string> lines = wrap(s1, len);
    stars(len);
    for (auto line : lines)
        cout << line << endl;
}

void test4(void)
{
    const size_t len = 52;
    const string s1 = string(
        "You toss a rock and knock a robin off a nearby fence."
    );

    list<string> lines = wrap(s1, len);
    stars(len);
    for (auto line : lines)
        cout << line << endl;
}

void test5(void)
{
    const size_t len = 52;
    const string s1 = string(
        "Gotta pee. This flowerbed looks like it needs some water. Synergy!"
    );

    list<string> lines = wrap(s1, len);
    stars(len);
    for (auto line : lines)
        cout << line << endl;
}

// Break 'input' into a list of sub-strings,
// each with a length less than 'limit'.
list<string> wrap(const string& input, size_t limit)
{
    assert(limit > 0);

    list<string> lines;
    size_t start = 0;   // sub-string start position
    size_t end = 0;     // sub-string end position
    size_t len = 0;     // sub-string length
    size_t length = input.length();     // what's left of input
    cout << '\t' << "length" << '\t' << length << endl;

    while (length > 0) {
        // Find the first non-space
        start = input.find_first_not_of(' ', end);
        cout << '\t' << "start" << '\t' << start << endl;
        if (start == string::npos)
            break; // no non-space left, we're done
        if (length <= limit) {
            lines.push_back(input.substr(start, length));
            break;
        }
        // Find the last space before the end of the current part
        end = input.find_last_of(' ', start + limit);
        cout << '\t' << "end" << '\t' << end << endl;
        if (end == string::npos)
            end = start + limit; // Didn't find a space, just chop it
        len = end - start;
        if (len > length)
            len = length; // If past the end, trim to what's left
        cout << '\t' << "len" << '\t' << len << endl;
        //cout << start <s '\t' << end << '\t' << len << '\t' << length << endl;
        // Put the current sub-string on the list
        lines.push_back(input.substr(start, len));
        length -= len;
        cout << '\t' << "length" << '\t' << length << endl;
    }

    return lines;
}

// read a file into a string, wrap lines at 'len' and print
void wrap_file(const char *file_name)
{
    char line[256];
    string contents;
    ifstream f(file_name);
    while (!f.eof()) {
        f.getline(line, 256);
        contents += line;
    }
    f.close();

    list<string> lines = wrap(contents, 79);
    for (auto line : lines)
        cout << line << endl;
}

