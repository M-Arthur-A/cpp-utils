#include "/home/arthur/Project/mySoft/Cpp/utilities/src/profile.h"
#include "/home/arthur/Project/mySoft/Cpp/utilities/src/paginator.hpp"
#include <rapidfuzz/fuzz.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <future>
#include <thread>
//#include <mutex>


struct Query {
public:
	Query (bool partial=true, unsigned int threads=1)
	: partial(partial)
	, threads(threads) {
		std::cout << "\nВведите последовательность для проверки:" << std::endl;
		where = getlines();
		std::cout << std::endl;
		std::cout << "Введите последовательность для поиска:" << std::endl;
		what = getlines();
	}

	void run () {
		if (threads == 1) {
			std::vector<std::vector<double>> resultMatrixTemp = spawnSearches({where.begin(), where.end()});
			resultMatrix.insert(resultMatrix.end(), resultMatrixTemp.begin(), resultMatrixTemp.end());

		} else {
			std::vector<std::future<std::vector<std::vector<double>>>> futures;
			int page_size	= where.size() / threads + 1;
			for (auto page : Paginate(where, page_size)) {
				futures.push_back(std::async([=] { return spawnSearches({page.begin(), page.end()}); }));
			}
			for (auto& f : futures) {
				auto resultMatrixTemp = f.get();
				resultMatrix.insert(resultMatrix.end(), resultMatrixTemp.begin(), resultMatrixTemp.end());
			}
		}
	}

	void printInitials() {
		std::cout << "Task is to find <" << what.size() << "> item(s) in <" << where.size()
				<< "> sentence(s)\nwith partial set to <" << partial << "> using <"
				<< threads << "> thread(s).\n" << std::endl;
	}

	void getResult () { printMatrix();}

private:
  bool partial;
  unsigned int threads;
  std::vector<std::string> where, what;
  std::vector<std::vector<double>> resultMatrix;
//  std::mutex m;

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

	std::vector<std::vector<double>> spawnSearches(IteratorRange<std::vector<std::string>::iterator> page) {
		std::vector<std::vector<double>> resultMatrixTemp;
		for (auto source : page) {
			std::vector<double> res;
			for (auto key : what)	{
				res.push_back(fuzzySearch(source, key));
			}
//			if (threads > 1) { std::lock_guard <std::mutex> g(m); }
			resultMatrixTemp.push_back(move(res));
		}
		return resultMatrixTemp;
	}

	double fuzzySearch (const std::string& source, const std::string& key) const {
		if (partial) { return rapidfuzz::fuzz::partial_ratio(source, key); }
		return rapidfuzz::fuzz::ratio(source, key);
	}

	void printMatrix () const {
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


Query argParse (int argc, const char** argv) {
	bool partial = true;
	unsigned int threads = 1;
	if (argc > 1) {
		for (int i = 1; i < argc; ++i) {
			std::string arg = argv[i];
			if (arg == "-f") {
			  partial = false;
			} else if (arg == "-t") {
				if (i+1 == argc) {
					threads = 0;
				} else {
					threads = std::atoll(argv[i+1]);
				}
			  if (threads == 0) {
			  	threads = std::thread::hardware_concurrency();
			  }
			} else if ((arg == "-h") | (arg == "--help")) {
				std::cout << "Данная программа отображает % похожести переданных текстов\n"
						<< "Работает в двух режимах: частичный поиск и полный поиск:\n"
						<< "-   для осуществления полного поиска добавьте ключ -f\n"
						<< "-   для осуществления частичного поиска ключ не требуется\n"
						<< "Так же есть возможность запустить программу в многопоточном режиме:\n"
						<< "-   для многопоточного режима добавте ключ -t и количество потоков (0 - выбрать количество ядер).\n"
						<< "Ваш компьютер имеет " << std::thread::hardware_concurrency() << " ядер.\n";
				exit(0);
			}
		}
	}
	return {partial, threads};
}


int main(int argc, const char** argv) {
	std::ios_base::sync_with_stdio(false); // optimization of stdin
	/* PRODUCTION */
///*
	LOG_DURATION("Время выполнения");
	Query Q = argParse(argc, argv);
	Q.run();
	Q.getResult();
//*/
	/* END PRODUCTION */

	/* TESTING */
/*
	std::string fileName = "../generate/gen100K.txt";
	//	std::istringstream cin("asd\n$\nsd\n$\n");
	{ LOG_DURATION("single thread");
	std::ifstream cin(fileName);
	std::cin.rdbuf(cin.rdbuf());
	const char* argv_new[] = { "fuzzy.cpp", "-s", "0" };
	Query Q = argParse(2, argv_new);
	Q.printInitials();
	Q.run();
//	Q.getResult();
	}

	{ LOG_DURATION("multiple thread");
	std::ifstream cin(fileName);
	std::cin.rdbuf(cin.rdbuf());
	const char* argv_new[] = { "fuzzy.cpp", "-t", "0" };
	Query Q = argParse(2, argv_new);
	Q.printInitials();
	Q.run();
//	Q.getResult();
	}
*/
	/* END of TESTING */
	return 0;
}
