// fileio.cpp
#include <fstream>
#include <iostream>
#include <string>

void write_to_file(int *array, int length, std::string& filename);
void read_from_file(const std::string& filename);
void init_array(int *array, int length);

static const int ARRAY_LENGTH = 20;

int main(int argc, char **argv)
{
	int array[ARRAY_LENGTH];
	std::string filename(argv[1]);

	init_array(array, ARRAY_LENGTH);
	write_to_file(array, ARRAY_LENGTH, filename);
	read_from_file(filename);

	return 0;
}


void write_to_file(int *array, int length, std::string& filename)
{
	std::basic_ofstream<int> out(filename, std::ios_base::binary);
	out.write(array, length * sizeof(int));
	out.close();
}

void read_from_file(const std::string& filename)
{
	std::basic_ifstream<int> in(filename, std::ios_base::binary);
	while (in) {
		int x = 0;
		in >> x;
		std::cout << x << std::endl;
	}
	in.close();
}

void init_array(int *array, int length)
{
	for (int i = 0; i < length; i++)
		array[i] = 1000 + (i + 100) * (i % 5);
}

