#include "controls.hpp"
#include "antSim.h"

// https://www.sfml-dev.org/tutorials/2.5/graphics-shader.php
// https://www.youtube.com/watch?v=q7QjRu7WEhE
// https://github.com/johnBuffer/AntSimulator


int main() {
  SimulationSettings settings;
  AntSim simulation(settings);

  return simulation.process();
}
