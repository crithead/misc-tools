/**
 * Check a file for tab characters '\t'
 *
 * Returns:
 *   -1 Error
 *    0 No tabs
 *    N Number of files with tabs
 */

#include <cstring>
#include <fstream>
#include <iostream>


int CheckFile(const char *);

static char TAB = '\t';
static bool messagesOn = true;

/* tabcheck [-v] file ... */
int main(int argc, char *argv[])
{
    int result = -1;
    int firstFile = 1;

    if (argc == 1) {
        std::cerr << "Usage: tabcheck [-v] file ..." << std::endl;
        return -1;
    }

    if ((argc > 1) && (strncmp(argv[1], "-v", 2) == 0)) {
        messagesOn = true;
        firstFile++;
    }

    for (int i = firstFile; i < argc; i++) {
       int n = CheckFile(argv[i]);
        if (n == -1) {
            std::cerr << "Failed to open file: " << argv[i] << std::endl;
            result = -1;
        } else if (messagesOn) {
            std::cout << argv[i] << ": " << n << std::endl;
            result += (n > 0) ? 1 : 0;
        }
    }

    return result;
}

/**
 * Check a file  for  tabs.
 * @param filename The name fo the file to check.
 * @return Number of tab characters in file.
 */
int CheckFile(const char *filename)
{
    int nTabs = 0;
    int nChars = 0;
    std::ifstream fs(filename);
    if (!fs.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return -1;
    }
    while (!fs.eof()) {
        char ch = 0;
        fs >> ch;
        if (ch != 0)
            nChars++;
        if (ch == TAB)
            nTabs++;
    }
    fs.close();
    return nTabs;
}

