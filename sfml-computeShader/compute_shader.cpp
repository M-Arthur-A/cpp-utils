#include <SFML/Graphics.hpp>
#include <iostream>
// #include <SFML/OpenGL.hpp>
// #include <SFML/Graphics/RenderWindow.hpp>
// #include <SFML/Window.hpp>
// #include <SFML/Config.hpp>
// #include <SFML/Graphics/Shader.hpp>
// https://dev.my-gate.net/2021/08/08/basic-fragment-shader-with-sfml/

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "OpenGL");
  window.setVerticalSyncEnabled(true);
  sf::Clock clock;
  // activate the window
  window.setActive(true);

  // load resources, initialize the OpenGL states, ...
  sf::Shader shader;
  if (!shader.loadFromFile("BasicCompute.compute", sf::Shader::Fragment)) {
    std::cerr << "Couldn't load fragment shader\n";
    return -1;
  }
  auto shape = sf::RectangleShape{ sf::Vector2f{ window.getSize() } };

  // run the main loop
  while (window.isOpen()) {
    // for (auto event = sf::Event{}; window.pollEvent(event);) {
    //     if (event.type == sf::Event::Closed) {
    //       window.close();
    //     }
    //     else if (event.type == sf::Event::MouseMoved) {
    //       mouse_position = window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
    //     }
    // draw...

    shader.setUniform("time", clock.getElapsedTime().asSeconds());

    window.clear();
    window.draw(shape, &shader);

    // end the current frame (internally swaps the front and back buffers)
    window.display();
  }
}
