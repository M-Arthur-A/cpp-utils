#include "get-screen.h"
#include "get-ocr.h"
#include "get-translate.h"

#include <chrono>
#include <thread>


int main() {
  std::string ENGtext(" "), previousENGtext(" "), RUtext(" ");
  cv::Mat img;

  for(;;) {
    screenshot(img, false);
    cv::Vec3b color = img.at<cv::Vec3b>(cv::Point(20,150));
    if (color[0] != 201 | color[1] != 217 | color[2] != 226) {
      std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
      continue;
    }

    OCRfromImg(ENGtext, img);
    std::cout << ENGtext << std::endl;

    translate("ggl", ENGtext, previousENGtext);

    // get little delay
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
  };
  return 0;
}
