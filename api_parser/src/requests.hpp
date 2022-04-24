#pragma once

#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <string>
#include <iostream>


class Response {
	Response (std::string r_): response(r_) {};

private:
	std::string response;
};

class Query {
	Query(std::string url_, std::string h_): url(url_), header(h_) {};

	Response Run() {
		curlpp::Cleanup myCleanup; // RAII cleanup
		return Response(curlpp::options::Url(url));
	};

private:
	std::string url;
	std::string header;
};


/*
	curlpp::Cleanup myCleanup; // RAII cleanup

	std::ostringstream os;
	os << curlpp::options::Url(std::string("http://example.com"));
	cout << os.str() << endl;
 */
