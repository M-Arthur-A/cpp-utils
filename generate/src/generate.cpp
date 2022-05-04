#include <iostream>
#include <fstream>
#include <string>
#include "/home/arthur/Project/mySoft/Cpp/utilities/src/profile.h"


class Generator {
public:
	Generator (std::string fname, unsigned int l_num, std::size_t l_size=50):
	  file_name(fname)
	, line_num(l_num)
	, line_size(l_size)
		{
			dict = "qw erta sd fgzx cvby uiop hjk lnm./,;";
			dict_size = dict.size();
		};

	int gen() {
		LOG_DURATION("generating file");
//    cout << std::numeric_limits<unsigned int>::max();
		std::ofstream out(file_name, std::ios_base::out);
		for (unsigned int i = 0; i < line_num; i++) {
			for (std::size_t ii = 0; ii < line_size; ii++) {
				int rand_symbol = genRand();
				out << dict[rand_symbol];
			}
			out << "\n";
		}
	  out << "$\n";
		return 0;
	}

	void print () {
		std::cout << "The task is to generate file \n    with <"
				<< file_name << "> name\n    with <"
				<< line_num  << "> lines\n    with <"
				<< line_size << "> symbols in each line. \n";
	}

	~Generator() {
		std::cout << "\nDONE\n";
	}

private:
	std::string file_name;
	unsigned int line_num;
	std::size_t line_size;
	std::string dict;
	std::size_t dict_size;

	int genRand() {
		return std::rand()/((RAND_MAX + 1u)/dict_size);
	}

};

int main () {
//	Generator g("gen.txt", 10'000'000);
	Generator g("gen.txt", 100'000);
	g.print();
	return g.gen();
}
