#include <rapidfuzz/fuzz.hpp>
#include <iostream>


struct Query {
public:
	Query (bool partial=true): partial(partial) {
		std::cout << "Введите последовательность для проверки:" << std::endl;
		where = getlines();
		std::cout << std::endl;
		std::cout << "Введите последовательность для поиска:" << std::endl;
		what = getlines();
	}

	void run () {
		for (auto source : where) {
			std::vector<double> res;
			for (auto key : what)	{
				res.push_back(fuzzySearch(source, key));
			}
			resultMatrix.push_back(res);
		}
	}

	void getResult () { printMatrix();}

private:
  bool partial;
  std::vector<std::string> where, what;
  std::vector<std::vector<double>> resultMatrix;

	std::vector<std::string> getlines() {
		std::vector<std::string> lines;
		std::string line;
		while (true)	{
			std::getline(std::cin, line);
			if (line == "$" || std::cin.eof()) {break;}
			lines.push_back(line);
		}
		return lines;
	}

	double fuzzySearch (const std::string& source, const std::string& key) const {
		if (partial) { return rapidfuzz::fuzz::partial_ratio(source, key); }
		return rapidfuzz::fuzz::ratio(source, key);
	}

	void printMatrix () {
		std::cout << "\n\nРезультат ";
		if (partial) {
			std::cout << "частичного ";
		} else {
			std::cout << "полного ";
		}
		std::cout << "вхождения (%):\n\n";

		// print header of Matrix
		std::cout << "Item";
		for (auto key : what)	{
			std::cout << "\t" << key;
		}
		std::cout << "\n";

		// print body of Matrix
		for (size_t i_source = 0; i_source < resultMatrix.size(); i_source++) {
			std::cout << where[i_source];
			auto vec_source = resultMatrix[i_source];

			for (size_t i_key = 0; i_key < vec_source.size(); i_key++)	{
				std::cout << "\t" << vec_source[i_key];
			}
			std::cout << "\n";
		}
	}
};


Query argParse (int& argc, char** argv) {
	bool partial = true;
	if (argc > 1) {
		std::string arg = argv[1];
		if (arg == "-f") { partial = false;}
		else { // (arg == "--help" || arg == "-h")
			std::cout << "Данная программа отображает % похожести переданных текстов\n"
					<< "Работает в двух режимах: частичный поиск и полный поиск.\n"
					<< "Для осуществления полного поиска добавьте ключ -f\n"
					<< "Для осуществления частичного поиска ключ не требуется\n";
			exit(0);
		}
	}
	return Query(partial);
}


int main(int argc, char** argv) {
	std::ios_base::sync_with_stdio(false); // optimization of stdin
	Query q = argParse(argc, argv);
	q.run();
	q.getResult();
}
