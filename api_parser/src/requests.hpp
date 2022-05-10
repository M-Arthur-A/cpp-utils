#pragma once

#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Infos.hpp>
#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <future>
#include <sstream>


class Query {
public:
	Query(std::string &url_, std::list<std::string> &h_): url(url_), header(h_) {
		curlpp::Cleanup myCleanup; // RAII cleanup
	};

	std::string Response() {
			Get();
			return move(std::string(responseText.str()));
	}

private:
	std::string url;
	std::list<std::string> header;
	curlpp::Easy request;
	std::ostringstream responseText;


	void Get() {
		request.setOpt(new curlpp::options::Url(url));
		request.setOpt(new curlpp::options::HttpHeader(header));
		request.setOpt(new curlpp::options::WriteStream(&responseText)); // result will go to response
		request.perform();
//		std::cout << curlpp::infos::ResponseCode::get(request);// << std::endl;
	};
};

std::string process(std::string url, std::list<std::string> headers) {
	Query q(url, headers);
	return q.Response();
}
