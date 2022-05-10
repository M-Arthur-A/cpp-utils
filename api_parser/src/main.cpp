#include <pugixml.hpp>
#include <fstream>
#include <iterator>
#include "requests.hpp"
#include "xhtml.h"

void parseDocCurlcpp () {
	std::list<std::string> headers;
	headers.push_back("User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:100.0) Gecko/20100101 Firefox/100.0");
	std::string url = "https://github.com/jpbarrette/curlpp/blob/master/examples/example02.cpp";
	Query q(url, headers);
	std::cout << q.Response() << std::endl;
}

void parseDocsCurlcpp () {
	std::vector<std::future<std::string>> results;
	int tutorialsCount = 24;
	std::string counter;
	std::list<std::string> headers;
	headers.push_back("User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:100.0) Gecko/20100101 Firefox/100.0");
	std::string url = "https://github.com/jpbarrette/curlpp/blob/master/examples/example";
	for (int i = 0; i <= tutorialsCount; ++i ) {
		if (std::to_string(i).size() == 1) {
			counter = "0" + std::to_string(i);
		} else {
			counter = std::to_string(i);
		}
		std::cout << counter << std::endl;
		results.push_back(std::async([=] { return process(url + counter + ".cpp", headers); }) );
	}

	std::ofstream ofs("results");
	for (auto &f : results) {
		ofs << f.get() << "\n";
	}
}

int main() {
//	parseDocsCurlcpp();
//	const char* html = "<title>Foo</title><p>Foo!";
	std::ifstream in_file("html.txt");
	std::string html(std::istreambuf_iterator<char>(in_file),
									 (std::istreambuf_iterator<char>()) );
	std::string xhtml;
	xhtml = CleanHTML( html.c_str() );
//	std::cout << xhtml;

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_string(xhtml.c_str());

	if (!result)
			return -1;

//	pugi::xpath_node_set nodes = doc.select_nodes("//td[@id='LC7']/span/text()");
//	pugi::xpath_node_set nodes = doc.select_nodes("//td[contains(@id,'LC')]/span//text()");
	pugi::xpath_node_set nodes = doc.select_nodes("//td[contains(@id,'LC')]/span");
	for (auto& node : nodes) {
		std::cout << node.node().value() << '\n';
	}
	return 0;
}
