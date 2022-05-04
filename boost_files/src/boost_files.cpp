/*** learning boost::https://habr.com/ru/company/yandex/blog/526538/ ***/
#include <boost/filesystem/operations.hpp>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>
#include <cassert>
#include <fstream>
#include <algorithm>
using namespace std;

void listFiles(const boost::filesystem::path &targetDir) {
		boost::filesystem::directory_iterator begin(targetDir);
		boost::filesystem::directory_iterator end;
		for (; begin != end; ++ begin) {
			boost::filesystem::file_status fs = boost::filesystem::status(*begin);
			switch (fs.type()) {
				case boost::filesystem::regular_file:
						std::cout << "FILE ";
						break;
				case boost::filesystem::symlink_file:
						std::cout << "SYMLINK ";
						break;
				case boost::filesystem::directory_file:
						std::cout << "DIRECTORY ";
						break;
				default:
						std::cout << "OTHER ";
						break;
			}
			if (fs.permissions() & boost::filesystem::owner_write) {
					std::cout << "W ";
			} else {
					std::cout << " ";
			}
			std::cout << *begin << '\n';
		}
}

void createDirs(const char* dir) {
	boost::system::error_code error;

	// creating folder and subfolder
	string strFilePath(dir);
	string pathToFile = strFilePath.substr(0, strFilePath.find_last_of('/'));
	boost::filesystem::create_directories(pathToFile, error);
	assert(!error);
}

void createFile(const char* filePath, const char* fileText) {
	// var to store errors (for not using slow try / catch)
	boost::system::error_code error;

	createDirs(filePath);

	std::ofstream ofs(filePath);
	ofs << fileText;
	assert(ofs);
	ofs.close();
	assert(!boost::filesystem::exists(fileText));
}

void readFile(const char* filePath) {
  const boost::interprocess::mode_t mode = boost::interprocess::read_only;
  boost::interprocess::file_mapping fm(filePath, mode);
  boost::interprocess::mapped_region region(fm, mode, 0, 0);

  const char* begin = static_cast<const char*>(
      region.get_address()
  );
  const char* pos = std::find(
      begin, begin + region.get_size(), '!'
  );
	cout << pos << endl;
}

void removeDirs(const char* dir) {
	boost::system::error_code error;
	boost::filesystem::remove_all(dir, error);
	assert(!error);
}

void removeFile(const char* filePath) {
	boost::system::error_code error;
	boost::filesystem::remove(filePath, error);
	assert(!error);
}

int main() {
//	listFiles("./");
//	createFile("./dir/subdir/file.txt", "Boost.Filesystem is fun!");
//	readFile("./dir/subdir/file.txt");
//	removeDirs("dir");
//	removeFile("todel.txt");
	return 0;
}
