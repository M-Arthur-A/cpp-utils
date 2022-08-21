#include "get-translate.h"
#include <cpr/api.h>
#include <cpr/cpr.h>
#include <iostream>
#include <algorithm>
#include <string>


void prepareQuery(std::string &query) {
  // NAME does not need translation
  auto PosNewLine = std::distance(query.begin(), std::find(query.begin(), query.end(), '\n'));
  std::cout << query.substr(0, PosNewLine) << ": ";
  query = query.substr(PosNewLine+1, query.size());
  std::replace(query.begin(), query.end(), ' ', '+');
  std::replace(query.begin(), query.end(), '\n', '+');
  for(auto mistakeIdx = query.find("++"); mistakeIdx != std::string::npos;) {
    query.erase(mistakeIdx, 1);
  }
  if (query.back() == '+') {
    query.pop_back();
  }
}

std::string gglTranslate(std::string &query) {
  cpr::Response r = cpr::Get(cpr::Url{ "https://translate.google.com/m?sl=en&tl=ru&hl=ru&q=" + query},
                             cpr::Header{ { "User-Agent",
                                            "Opera/9.80 (Android; Opera Mini/11.0.1912/37.7549; U; pl) Presto/2.12.423 Version/12.16" },
                                          { "Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8" },
                                          { "Accept-Language", "en-US,en;q=0.5" },
                                          { "DNT", "1" },
                                          { "Upgrade-Insecure-Requests", "1" },
                                          { "Cache-Control", "no-cache" },
                                          { "Pragma", "no-cache" },
                                        } );
  if(r.status_code == 200) {
    std::string::size_type res_start = r.text.find(R"(<div class="result-container">)") + 30;
    std::string::size_type res_stop  = r.text.find(R"(</div>)", res_start);
    return r.text.substr(res_start, res_stop - res_start);
  }

  return "error";
}



void translate(std::string provider, std::string &query, std::string &queryPrevious) {
  if (query != queryPrevious && !query.empty()) {
    queryPrevious = query;
  } else {
    return;
  }

  prepareQuery(query);
  if (provider == "ggl") {
    std::cout << gglTranslate(query) << '\n'<< std::endl;
  }
}
