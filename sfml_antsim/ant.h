#pragma once

#include "controls.hpp"
#include "utils.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Window.hpp>
#include <set>

using Vectors2D = std::set<sf::Vector2i>;

class Ant : public sf::Drawable, public sf::Transformable  {
private:
  struct Particle {
    sf::Vector2f velocity;
    sf::Time lifetime;
  };

  SimulationSettings* settings;
  float time = 0;
  sf::Vector2f curPos; // ant's position
  float curSize;       // ant's size
  sf::Color curColor;  // ant's main color
  float curAngle;      // ugol (direction)
  float curSpeed;      // ant's speed
  float trailWidth = 2;
  float trailLength = 500;
  std::set<sf::Vector2i> *_TrailMap = nullptr;

  std::vector<Particle> trails;
  sf::VertexArray m_vertices;

public:
  // std::vector<sf::RectangleShape> trails;
  // std::vector<sf::CircleShape> trails;


  Ant(SimulationSettings* _settings);
  ~Ant();

  void _init();

  void _process(float delta);

  void _doRectangle(sf::Vector2f lastPos, sf::Vector2f newPos);

  void drawTrail();

  void drawSensors(sf::Vector2f pos, int sensorSize);

  void setTrailMap(Vectors2D *TrailMap_) { _TrailMap = TrailMap_; };

  float sense(float sensorAngleOffset, float sensorOffsetDst, int sensorSize);

  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

  void setPos(sf::Vector2f position);
  sf::Vector2f getPos() { return curPos; };

  void setColor(sf::Color newColor);
  sf::Color getColor() { return curColor; };

  void setSize(float newSize);
  float getSize() { return curSize; };

  void setTrailSize(float tSize);

  void setAngle(float newAngle);
  float getAngle() { return curAngle; };

  void setSpeed(float newSpeed);
};
