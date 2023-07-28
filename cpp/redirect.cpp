/* redirect.cpp
 * Redirect stdout to a file.
 * To redirect stdout to somewhere else by reopening the file pointer.
 */
#include <iostream>
#include <cstdio>
#include <ctime>

int main(int argc, char **argv) 
{
    std::cout << "This is before reopening stdout as a file." << std::endl;

    if (freopen("stdout.txt", "w", stdout) == NULL) {
        std::cerr << "redirect failed" << std::endl;
        return 1;
    }

    std::cout << "This is AFTER reopening stdout as a file." << std::endl;
    std::cout << "So this should be in a file, not to the console." << std::endl;
    std::cout << "Timestamp:" << time(0) << std::endl;

    fclose(stdout);
    return 0;
}

