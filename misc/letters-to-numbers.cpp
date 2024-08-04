/*
text to numbers

Translates a text string letters (a-z) into numbers (1-26).
*/

#include <cctype>
#include <iostream>
#include <sstream>
#include <string>

class text_string
{
private:
    void letters_to_numbers() {
        for (size_t i = 0; i < letters.length(); i++) {
            char c = letters[i];
            if (isalpha(c)) {
                std::stringstream ss;
                if (last_digit)
                    ss << (1 + toupper(c) - 'A') % 10;
                else
                    ss << 1 + toupper(c) - 'A';
                numbers.append(ss.str());
            }
        }
    }
    std::string letters;
    std::string numbers;
    // Setting 'last_digit' to true stores only the ones digit of the number
    // to be used instead of the entire number.  It strips the tens digit.
    // It reduces the number of 1s and 2s in the output string.
    bool last_digit;
public:
    text_string(const char *s, bool last_digit_only = false)
            : letters(s), last_digit(last_digit_only) {
        letters_to_numbers();
    }
    ~text_string() {}
    const std::string& as_letters() const {
        return letters;
    }
    const std::string& as_numbers() const {
        return numbers;
    }
};

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; i++) {
        text_string s1(argv[i]);
        std::cout << s1.as_letters() << std::endl; 
        std::cout << s1.as_numbers() << std::endl; 
        text_string s2(argv[i], true);
        std::cout << s2.as_numbers() << std::endl; 
        std::cout << std::endl; 
    }

    return 0;
}

