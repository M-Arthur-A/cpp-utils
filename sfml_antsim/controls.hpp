#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
// here will be controls to set ants value, speed, color etc
// https://github.com/eliasdaler/imgui-sfml
// https://www.sfml-dev.org/tutorials/1.6/window-events.php

struct SimulationSettings {
  int screenWIDTH = 2560;
  int screenHEIGHT = 1440;
  sf::Color backgroundCOLOR = {98, 114, 164};

  float antSPEED = 2.0;
  int antCOUNT = 10;
  float antSIZE = 5.0;
  float antPATHSIZE = 100;


  sf::Color antCOLOR = {139, 233, 253};
  int sensorSIZE = 10;
  float sensorTURNSPEED = 3;
  float sensorANGLEOFFSET = 5;
  float sensorOFFSETDST = 2;
};
