#pragma once
#include <algorithm>
#include <string>


void prepareQuery(std::string &query);

std::string gglTranslate(std::string &query);

void translate(std::string provider, std::string &query);
