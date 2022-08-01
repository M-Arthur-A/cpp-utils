#include "ant.h"
#include "controls.hpp"
#include "utils.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <math.h>

Ant::Ant(SimulationSettings* _settings): settings(_settings)
                                       , trails(_settings->antPATHSIZE)
                                       , m_vertices(sf::Points, _settings->antPATHSIZE) {
  setSize(settings->antSIZE);
  setTrailSize(settings->antPATHSIZE);
  setColor(settings->antCOLOR);
  setSpeed(settings->antSPEED);
}

Ant::~Ant() {

}

void Ant::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  // apply the transform
  states.transform *= getTransform();

  // our particles don't use a texture
  states.texture = NULL;

  // draw the vertex array
  target.draw(m_vertices, states);
}

void Ant::_init() {
  // init trail to ant
  // Line2D* trail = Line2D::_new();
  // Ref<Gradient> gradient;
  // gradient.instance();
  // PoolColorArray colors;
  // colors.push_back(Color(1,0,0,0));
  // colors.push_back(Color(1,0,0,0.5));
  // gradient->set_colors(colors);
  // trail->set_gradient(gradient);
  // trail->set_as_toplevel(true);
  // trail->set_width(trailWidth*2);
  // add_child(trail);
}

void Ant::_doRectangle(sf::Vector2f lastPos, sf::Vector2f newPos) {
  // https://poschitat.online/ugly-pryamougolnogo-treugolnika
  // делаем прямоугольный треугольник из начала координат
  Rect r;
  r.vecA = lastPos;
  r.vecB = newPos;
  float y = r.vecB.y - r.vecA.y;
  float x = r.vecB.x - r.vecA.x;
  r.size = std::hypot(x, y); // same as: std::sqrt(x*x + y*y);
  r.angle = std::atan(y / x) * 180 / M_PI;
  sf::RectangleShape trail(sf::Vector2f(r.size, settings->antSIZE));
  trail.setPosition(r.vecA.x, r.vecA.y);
  trail.setFillColor(settings->antCOLOR);
  trail.rotate(r.angle);
  // trails.push_back(trail);
}

void Ant::drawTrail() {
  // // _doRectangle(lastPos, newPos);
  // sf::CircleShape trail(trailWidth, 3);
  // trail.setPosition(curPos);
  // trails.push_back(trail);
  // // _TrailMap->insert(static_cast<sf::Vector2i>(newPos));
  // while (trails.size() > trailLength) {
  //   // delete from TrailMap
  //   // _TrailMap->erase(static_cast<sf::Vector2i>(*(trails.begin())));
  //   trails.erase(trails.begin());
  // }
  for (std::size_t i = 0; i < trails.size(); ++i) {
    Particle &p = trails[i];

    // update the position of the corresponding vertex
    m_vertices[i].position += p.velocity * elapsed.asSeconds();

    // update the alpha (transparency) of the particle according to its
    // lifetime
    float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
    m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
  }
}

void Ant::drawSensors(sf::Vector2f pos, int sensorSize) {
  // sf::Vector2f position = Vector2(pos.x-sensorSize, pos.y-sensorSize);
  // ColorRect* sensor = ColorRect::_new();
  // sensor->set_position(position);
  // sensor->set_size(Vector2(sensorSize*2, sensorSize*2));
  // sensor->set_frame_color(Color(1, 0, 0, 1));
  // // sensor->set_frame_color(Color(0, 0, 1, 1));
  // add_child(sensor);
  // // sensor->add_child_below_node(get_parent(), this);
  // // get_parent()->add_child(sensor);

  // // CanvasItem* canvasItem;
  // // canvasItem->draw_line(Vector2(200, 100), Vector2(200, 1000), Color(255, 255, 255, 1));
}

float Ant::sense(float sensorAngleOffset, float sensorOffsetDst, int sensorSize) {
  // float sensorAngle = curAngle + sensorAngleOffset;
  // sf::Vector2f sensorDir = Vector2(cos(sensorAngle), sin(sensorAngle));
  // sf::Vector2i sensorCentre(curPos + sensorDir * sensorOffsetDst);

  // drawSensors(Vector2(sensorCentre.x, sensorCentre.y), sensorSize);

  // // std::cout << curPos << '\t' << sensorCentre << std::endl;
  // /*
  // Line2D* trail = (get_children())[0];
  // if (trail->get_point_count() == 10){
  // std::cout << "==========================================================================================" << std::endl;
  // std::cout << "curPos is " << curPos << std::endl;
  // std::cout << "centorPos is " << sensorCentre << std::endl;
  // std::cout << "centorDir is " << sensorDir << std::endl;
  // std::cout << "centorDir*Dst is " << sensorDir*sensorOffsetDst << std::endl;
  // std::cout << "sensorSize is " << sensorSize << std::endl;
  // std::cout << "censorAngleOffset is " << sensorAngleOffset << std::endl;
  // std::cout << "sentorPos check from " << sensorCentre.x - sensorSize << ":" << sensorCentre.y - sensorSize << std::endl;
  // std::cout << "sentorPos check to   " << sensorCentre.x + sensorSize << ":" << sensorCentre.y + sensorSize << std::endl;
  // std::cout << "trail path: ";
  // for (int i = 0; i < trail->get_point_count(); ++i) {
  //   sf::Vector2f trailPos = trail->get_point_position(i);
  //   std::cout << trailPos <<", ";
  // }
  // std::cout << std::endl;
  // std::cout << "==========================================================================================" << std::endl;
  // }
  // */
  float sum = 0;
  // sf::Vector2i pos;
  // for (int offsetX = -sensorSize; offsetX <= sensorSize; ++offsetX) {
  //   for (int offsetY = -sensorSize; offsetY <= sensorSize; ++offsetY) {
  //     pos = sensorCentre + Vector2i(offsetX, offsetY);
  //     // std::cout << "cur pos: " << curPos.x << ' ' << curPos.y << std::endl;
  //     // std::cout << "find pos: " << pos.x << ' ' << pos.y << std::endl;
  //     if (_TrailMap->size() > 0) {
  //       if (pos.x >= 0 && pos.x < WIDTH && pos.y >= 0 && pos.y < HEIGHT) {
  //         // std::cout << (*(_TrailMap->begin())).x << std::endl;
  //         auto it = _TrailMap->find(pos);
  //         if (it != _TrailMap->end()) {
  //           sum += pos.x;
  //         }
  //       }
  //     }
  //   }
  // }
  return sum;
}

void Ant::_process(float delta) {
  time += delta;

  // move Ant based on direction and speed
  sf::Vector2f direction = sf::Vector2f(cos(curAngle), sin(curAngle));
  sf::Vector2f newPos = curPos + direction * curSpeed;

  // set borders and setting new position and angle if ant hits border
  if (newPos.x < 0 || newPos.x >= settings->screenWIDTH || newPos.y < 0 || newPos.y >= settings->screenHEIGHT) {
    newPos.x = std::min((float)settings->screenWIDTH  - (float)0.01, std::max((float)0.0, (float)newPos.x));
    newPos.y = std::min((float)settings->screenHEIGHT - (float)0.01, std::max((float)0.0, (float)newPos.y));
    float random = hash(curPos.x * curPos.y + hash(time)) / 4294967295.0;
    curAngle = random * 2.0 * M_PI;
  }



  // steer based on sensory data
  // const int sensorSize = 10;
  // const float sensorTurnSpeed = 20;
  // const float sensorAngleOffset = 3.15;
  // const float sensorOffsetDst = 20;

  // float weightForward = sense(0, sensorOffsetDst, sensorSize);
  // float weightLeft    = sense(sensorAngleOffset, sensorOffsetDst, sensorSize);
  // float weightRight   = sense(-sensorAngleOffset, sensorOffsetDst, sensorSize);
  // // std::cout << weightForward << '\t' << weightLeft << '\t' << weightRight << std::endl;

  // float randomSteerStrength = hash(curPos.x * curPos.y + hash(time)) / 4294967295.0;

  // /*
  // if (_TrailMap->size() > 127) {
  //   std::cout << _TrailMap->size() << std::endl;
  //   for (auto& t : *_TrailMap) {
  //     std::cout << t << ' ';
  //   }
  //   std::cout << std::endl;
  // }
  // */
  // // continue in same direction
  // if (weightForward > weightLeft && weightForward > weightRight) {
  //   curAngle += 0;
  // }
  // // turn randomly
  // if (weightForward < weightLeft && weightForward < weightRight) {
  //   curAngle += (randomSteerStrength - 0.5) * sensorTurnSpeed / 200;
  // }
  // // turn right
  // if (weightRight > weightLeft) {
  //   curAngle -= randomSteerStrength * sensorTurnSpeed / 200;
  // }
  // // turn left
  // if (weightLeft > weightRight) {
  //   curAngle += randomSteerStrength * sensorTurnSpeed / 200;
  // }

  // // move Ant based on direction and speed
  // sf::Vector2f direction = Vector2(cos(curAngle), sin(curAngle));
  // sf::Vector2f newPos = curPos + direction * curSpeed;

  // // set borders and setting new position and angle if ant hits border
  // if (newPos.x < 0 || newPos.x >= WIDTH || newPos.y < 0 || newPos.y >= HEIGHT) {
  //   newPos.x = std::min((float)WIDTH -(float)0.01, std::max((float)0.0, (float)newPos.x));
  //   newPos.y = std::min((float)HEIGHT-(float)0.01, std::max((float)0.0, (float)newPos.y));
  //   float random = hash(curPos.x * curPos.y + hash(time)) / 4294967295.0;
  //   curAngle = random * 2.0 * M_PI;
  // }

  setPos(newPos);
  drawTrail();
}

void Ant::setPos(sf::Vector2f position) {
  curPos = position;
}

void Ant::setColor(sf::Color newColor) {
  curColor = newColor;
}

void Ant::setSize(float newSize) {
  curSize = newSize;
  trailWidth = newSize;
}

void Ant::setAngle(float newAngle) {
  curAngle = newAngle;
}

void Ant::setTrailSize(float tSize) {
  trailLength = tSize;
}

void Ant::setSpeed(float newSpeed) {
  curSpeed = newSpeed;
}


class ParticleSystem : public sf::Drawable, public sf::Transformable {
public:
  ParticleSystem(unsigned int count)
      : trails(count), m_vertices(sf::Points, count),
        m_lifetime(sf::seconds(3.f)), m_emitter(0.f, 0.f) {}

  void setEmitter(sf::Vector2f position) { m_emitter = position; }

  void update(sf::Time elapsed) {
    for (std::size_t i = 0; i < trails.size(); ++i) {
      // update the particle lifetime
      Particle &p = trails[i];
      p.lifetime -= elapsed;

      // if the particle is dead, respawn it
      if (p.lifetime <= sf::Time::Zero)
        resetParticle(i);

      // update the position of the corresponding vertex
      m_vertices[i].position += p.velocity * elapsed.asSeconds();

      // update the alpha (transparency) of the particle according to its
      // lifetime
      float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
      m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
    }
  }

private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // our particles don't use a texture
    states.texture = NULL;

    // draw the vertex array
    target.draw(m_vertices, states);
  }

private:
  struct Particle {
    sf::Vector2f velocity;
    sf::Time lifetime;
  };

  void resetParticle(std::size_t index) {
    // give a random velocity and lifetime to the particle
    float angle = (std::rand() % 360) * 3.14f / 180.f;
    float speed = (std::rand() % 50) + 50.f;
    trails[index].velocity =
        sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
    trails[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

    // reset the position of the corresponding vertex
    m_vertices[index].position = m_emitter;
  }

  std::vector<Particle> trails;
  sf::VertexArray m_vertices;
  sf::Time m_lifetime;
  sf::Vector2f m_emitter;
};

int doParticles() {
  // create the window
  sf::RenderWindow window(sf::VideoMode(512, 256), "Particles");

  // create the particle system
  ParticleSystem particles(1000000);

  // create a clock to track the elapsed time
  sf::Clock clock;

  // run the main loop
  while (window.isOpen()) {
    // handle events
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    // make the particle system emitter follow the mouse
    sf::Vector2i mouse = sf::Mouse::getPosition(window);
    particles.setEmitter(window.mapPixelToCoords(mouse));

    // update it
    sf::Time elapsed = clock.restart();
    particles.update(elapsed);

    // draw it
    window.clear();
    window.draw(particles);
    window.display();
  }

  return 0;
}
