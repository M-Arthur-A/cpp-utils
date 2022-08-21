#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XShm.h>
#include <cstddef>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <opencv4/opencv2/opencv.hpp>
#include <time.h>
/*
 * https://stackoverflow.com/a/39781697
 */

#define FPS(start) (CLOCKS_PER_SEC / (clock()-start))


struct ScreenShot{
  ScreenShot(uint x, uint y, uint width, uint height, bool needDemo):
               x(x), y(y), width(width), height(height){
    // shm - shared memory

    display = XOpenDisplay(nullptr);
    root = DefaultRootWindow(display);
    XGetWindowAttributes(display, root, &window_attributes);
    screen = window_attributes.screen;

    /*
    ximg = XShmCreateImage(display, DefaultVisualOfScreen(screen), DefaultDepthOfScreen(screen), ZPixmap, NULL, &shminfo, width, height);
    shminfo.shmid = shmget(IPC_PRIVATE, ximg->bytes_per_line * ximg->height, IPC_CREAT|0777);
    shminfo.shmaddr = ximg->data = (char*)shmat(shminfo.shmid, 0, 0);
    shminfo.readOnly = false;
    if(shminfo.shmid < 0) {
      std::cout << "Fatal shminfo error!\n";
    }
    Status s1 = XShmAttach(display, &shminfo);
    if (needDemo) {
      printf("XShmAttach() %s\n", s1 ? "success!" : "failure!");
    }

    init = true;
    */

    ximg = XGetImage(display, root, x, y, width, height, AllPlanes, ZPixmap);
  }

    void operator() (cv::Mat& cv_img){
    /*
    if(init)
        init = false;
    XShmGetImage(display, root, ximg, x, y, 0x00ffffff);
    */
    int BitsPerPixel = ximg->bits_per_pixel;
    std::vector<uint8_t> pixels;
    pixels.resize(width * height * 4);
    memcpy(&pixels[0], ximg->data, pixels.size());
    cv_img = cv::Mat(height, width, CV_8UC4, ximg->data);
  }

  void cleaner(cv::Mat& cv_img) {
    // cv::imwrite("maskNo.png", cv_img);
    // Convert RGBA data to grayscale data
    cv::cvtColor(cv_img, cv_img, cv::COLOR_RGBA2GRAY);

    // masking
    cv::Mat botMask, upMask;
    cv::Mat cropBotMask, cropUpMask;
    cv::Mat croppedBot, croppedUp;
    cv::threshold(cv_img, botMask, 50, 255, cv::THRESH_BINARY_INV);
    cv::threshold(cv_img, upMask, 230, 255, cv::THRESH_BINARY);

    cropBotMask = cv::Mat::zeros(cv_img.rows, cv_img.cols, CV_8U);
    cropBotMask(cv::Rect(50,67,1000,160)) = 1;
    botMask.copyTo(croppedBot, cropBotMask);

    cropUpMask = cv::Mat::zeros(cv_img.rows, cv_img.cols, CV_8U);
    cropUpMask(cv::Rect(50,10,300,50)) = 1;
    upMask.copyTo(croppedUp, cropUpMask);
    // blend together
    // Convert Mat to float data type
    croppedUp.convertTo(croppedUp, CV_32FC3);
    croppedBot.convertTo(croppedBot, CV_32FC3);

    // Normalize the alpha mask to keep intensity between 0 and 1
    cropUpMask.convertTo(cropUpMask, CV_32FC3, 1.0/255); //

    // Storage for output image
    cv_img = cv::Mat::zeros(croppedUp.size(), croppedUp.type());

    // Multiply the foreground with the alpha matte
    cv::multiply(cropUpMask, croppedUp, croppedUp);

    // Multiply the background with ( 1 - alpha )
    cv::multiply(cv::Scalar::all(1.0)-cropUpMask, croppedBot, croppedBot);

    // Add the masked foreground and background.
    cv::add(croppedUp, croppedBot, cv_img);

    // Display image
    // cv::imwrite("masked.png", cv_img);
    // imshow("Result", cv_img);
    // cv::waitKey();

    //
  }

  ~ScreenShot(){
    // if(!init)
    //   XDestroyImage(ximg);

    XDestroyImage(ximg);
    /*
    XShmDetach(display, &shminfo);
    shmdt(shminfo.shmaddr);
    */
    XCloseDisplay(display);
  }

  Display* display;
  Window root;
  XWindowAttributes window_attributes;
  Screen* screen;
  XImage* ximg;
  int x, y, width, height;
  /*
  XShmSegmentInfo shminfo;
  bool init;
  */
};


void screenshot(cv::Mat &img, bool needDemo=false) {
  ScreenShot screen(730, 1120, 1100, 250, needDemo); // x, y, resolution of the window to capture

  for(uint i;; ++i) {
    double start = clock();

    screen(img);

    /* find pixel with certain color in dialog frame
    cv::Vec3b color = img.at<cv::Vec3b>(cv::Point(20,150));
    std::cout << color << std::endl;
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
    img.at<cv::Vec3b>(cv::Point(20,150)) = color;
    imshow("Result", img);
    cv::waitKey();
    */

    if(!(i & 0b111111)) {
      if(needDemo) {
        printf("fps %4.f  spf %.4f\n", FPS(start), 1 / FPS(start));
      }
      break;
    }
  }

  cv::Vec3b color = img.at<cv::Vec3b>(cv::Point(20,150));
  if (!((color[0] == 201) && (color[1] == 217) && (color[2] == 226))) {
    // std::cout << color << std::endl;
    // img.setTo(cv::Scalar::all(0)); // make all black
    return;
  }

  screen.cleaner(img);

  if(needDemo) {
    // demontrate capture window
    cv::imshow("img", img);
    cv::waitKey(0);
  }
}
