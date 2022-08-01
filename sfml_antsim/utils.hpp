#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

// Hash function www.cs.ubc.ca/~rbridson/docs/schechter-sca08-turbulence.pdf
inline unsigned hash(unsigned state) {
  state ^= 2747636419u;
  state *= 2654435769u;
  state ^= state >> 16;
  state *= 2654435769u;
  state ^= state >> 16;
  state *= 2654435769u;
  return state;
}

template<class T>
T random(T _min, T _max) {
  return _min + T(std::rand()) / RAND_MAX * (_max - _min);
}

struct Rect {
  sf::Vector2f vecA;
  sf::Vector2f vecB;
  float size;
  float angle;
};
