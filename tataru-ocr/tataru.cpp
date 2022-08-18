#include "get-screen.h"
#include "get-ocr.h"
#include "get-translate.h"

#include <iostream>
#include <string>
#include <chrono>
#include <thread>


int main() {
  std::string ENGtext(" "), previousENGtext(" "), RUtext(" ");
  cv::Mat img;
  bool pause(false);

  for(;;) {
    screenshot(img, false);

    OCRfromImg(ENGtext, img);
    // std::cout << ENGtext << std::endl;

    if (ENGtext != previousENGtext) {
      translate("ggl", ENGtext);
      previousENGtext = ENGtext;
    }

    // get little delay
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
  };
  return 0;
}
