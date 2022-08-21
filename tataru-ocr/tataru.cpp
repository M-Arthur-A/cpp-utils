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

    // check if img is not dialog: screenshot return img with 1 channel (grayscale)
    if (img.channels() != 1) {
      continue;
    }

    OCRfromImg(ENGtext, img);
    // std::cout << ENGtext << std::endl;

    translate("ggl", ENGtext, previousENGtext);

    // get little delay
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
  };
  return 0;
}
