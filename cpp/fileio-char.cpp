// fileio.cpp
#include <fstream>
#include <iostream>
#include <string>

void write_to_file(char *array, int length, std::string& filename);
void read_from_file(const std::string& filename);
void init_array(char *array, int length);

static const int ARRAY_LENGTH = 20;

int main(int argc, char **argv)
{
	char array[ARRAY_LENGTH];

	if (argc <= 1) {
		std::cout << "fileio <filename>" << std::endl;
		return 1;
	}

	std::string filename(argv[1]);

	init_array(array, ARRAY_LENGTH);
	write_to_file(array, ARRAY_LENGTH, filename);
	read_from_file(filename);

	return 0;
}


void write_to_file(char *array, int length, std::string& filename)
{
	std::ofstream out(filename.c_str(), std::ios_base::binary);
	out.write(array, length * sizeof(char));
	out.close();
}

void read_from_file(const std::string& filename)
{
	std::ifstream in(filename.c_str(), std::ios_base::binary);
	while (in) {
		char x;
		in >> x;
		std::cout << x << std::endl;
	}
	in.close();
}

void init_array(char *array, int length)
{
	for (int i = 0; i < length; i++)
		array[i] = 'A' + ((11 * i) % 26);
}

