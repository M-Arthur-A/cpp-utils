#pragma once
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XShm.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <opencv4/opencv2/opencv.hpp>
#include <time.h>
#include <iostream>

struct ScreenShot {
  Display* display;
  Window root;
  XWindowAttributes window_attributes;
  Screen* screen;
  XImage* ximg;
  XShmSegmentInfo shminfo;
  int x, y, width, height;
  bool init;

  ScreenShot(uint x, uint y, uint width, uint height, bool needDemo);

  void operator() (cv::Mat& cv_img);

  void cleaner(cv::Mat& cv_img);

  ~ScreenShot();
};

void screenshot(cv::Mat &img, bool needDemo=false);
