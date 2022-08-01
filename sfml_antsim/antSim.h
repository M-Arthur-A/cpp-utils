#pragma once

#include "controls.hpp"
#include "ant.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>
#include <vector>
#include <set>

class AntSim {
  float time = 0;
  SimulationSettings& settings;

  void _init();
  void _spawn(sf::Vector2f position, float angle);
  void _updateSimulation(sf::Clock deltaClock);
public:
  std::vector<Ant> ants;
  sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(640, 480), "");
  std::set<sf::Vector2i> TrailMap;

  AntSim(SimulationSettings& setts): settings(setts) {};
  // ~AntSim();

  int process();
};
