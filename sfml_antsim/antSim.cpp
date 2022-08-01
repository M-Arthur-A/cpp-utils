#include "antSim.h"
#include "ant.h"
#include "utils.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>
#include <ois/OIS.h>
#include <cmath>
#include <imgui-SFML.h>
#include <imgui.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <ois/OISKeyboard.h>
#include <vector>


void AntSim::_spawn(sf::Vector2f position, float angle) {
  Ant ant(&settings);
  ant.setPos(position);
  ant.setAngle(angle);
  ant.setTrailMap(&TrailMap);
  ants.push_back(ant);
}

void AntSim::_init() {
  int width, height;
  float angle;
  const float cWidth  = static_cast<float>(settings.screenWIDTH) / 2;
  const float cHeight = static_cast<float>(settings.screenHEIGHT) / 2;
  const float radius  = 300.0;

  for (int i = 1; i <= settings.antCOUNT; ++i) {
    angle  = random(0.0, 2.0) * M_PI;
    width  = cWidth  + radius*cos(angle);
    height = cHeight + radius*sin(angle);
    _spawn(sf::Vector2f(std::move(width), std::move(height)), angle);
  }
}

void AntSim::_updateSimulation(sf::Clock deltaClock) {
  for (auto& ant : ants) {
    ant._process(deltaClock.getElapsedTime().asSeconds());
    for (auto& trail: ant.trails) {
      window->draw(trail);
    }
  }
}

int AntSim::process() {
  bool is_started = false;
  sf::Clock deltaClock;
  window->setVerticalSyncEnabled(true);
  window->setTitle("Ant simulation");


  ImGui::SFML::Init(*window);
  float antSetsColor[3] = {static_cast<float>(settings.antCOLOR.r),
                           static_cast<float>(settings.antCOLOR.g),
                           static_cast<float>(settings.antCOLOR.b)};
  float bgSetsColor[3]  = {static_cast<float>(settings.backgroundCOLOR.r),
                           static_cast<float>(settings.backgroundCOLOR.g),
                           static_cast<float>(settings.backgroundCOLOR.b)};
  while (window->isOpen()) {
    sf::Event event;
    while (window->pollEvent(event)) {
      ImGui::SFML::ProcessEvent(event);

      if (event.type == sf::Event::Closed) {
          window->close();
      }
    }
    ImGui::SFML::Update(*window, deltaClock.restart());
    ImGui::Begin("Simulation settings", NULL, ImGuiWindowFlags_None); // start window
    ImGui::InputInt("resolution width", &settings.screenWIDTH);
    ImGui::InputInt("resulution height", &settings.screenHEIGHT);
    ImGui::SliderFloat("ant speed", &settings.antSPEED, 2.0f, 10.0f);
    ImGui::InputInt("ant count", &settings.antCOUNT);
    ImGui::SliderFloat("ant size", &settings.antSIZE, 2.0f, 10.0f);
    ImGui::SliderFloat("ant path size", &settings.antPATHSIZE, 10.0f, 1000.f);
    ImGui::SliderInt("sensor size", &settings.sensorSIZE, 2, 10);
    ImGui::SliderFloat("sensor turn speed", &settings.sensorTURNSPEED, 1.0f, 10.0f);
    ImGui::SliderFloat("sensor angle offset", &settings.sensorANGLEOFFSET, 1.0f, 10.0f);
    ImGui::SliderFloat("sensor offset destination", &settings.sensorOFFSETDST, 1.0f, 10.0f);
    if (ImGui::ColorEdit3("ant color", antSetsColor)) {
      settings.antCOLOR.r = static_cast<sf::Uint8>(antSetsColor[0] * 255.f);
      settings.antCOLOR.g = static_cast<sf::Uint8>(antSetsColor[1] * 255.f);
      settings.antCOLOR.b = static_cast<sf::Uint8>(antSetsColor[2] * 255.f);
    }
    if (ImGui::ColorEdit3("background color", bgSetsColor)) {
      settings.backgroundCOLOR.r = static_cast<sf::Uint8>(bgSetsColor[0] * 255.f);
      settings.backgroundCOLOR.g = static_cast<sf::Uint8>(bgSetsColor[1] * 255.f);
      settings.backgroundCOLOR.b = static_cast<sf::Uint8>(bgSetsColor[2] * 255.f);
    }
    if (ImGui::Button("START") | ImGui::IsKeyDown(OIS::KC_SPACE)) {
      is_started = true;
      _init(); // start simulation
    }
    ImGui::End(); // end window

    window->clear(settings.backgroundCOLOR); // fill window with background color

    if (is_started) {
      _updateSimulation(deltaClock);
    }

    ImGui::SFML::Render(*window);
    window->display();
  }

  ImGui::SFML::Shutdown();
  return 1;
}
