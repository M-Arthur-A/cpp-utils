// https://medium.com/@daniel.coady/compute-shaders-in-opengl-4-3-d1c741998c03
// https://github.com/pondodev/opengl_compute

#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "shader.h"
#include "compute.h"
#include "batch_renderer.h"

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500


void framebuffer_size_callback( GLFWwindow* window, int width, int height ) {
  // callback function to handle when the window resizes
  glViewport( 0, 0, width, height );
}

int main() {
  #pragma region glfw setup

  // init glfw and some settings
  glfwInit();
  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
  glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

  // create window object
  GLFWwindow* window = glfwCreateWindow(
    WINDOW_WIDTH,
    WINDOW_HEIGHT,
    "compute shader test",
    NULL,
    NULL );

  // ensure creation was successful
  if ( window == NULL ) {
    std::cerr << "failed to create glfw window" << std::endl;
    glfwTerminate();
    return -1;
  }

  // set context
  glfwMakeContextCurrent( window );

  // load glad before we make any opengl calls
  if ( !gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress ) ) {
    std::cerr << "failed to initialise glad" << std::endl;
    return -1;
  }

  // set gl viewport size, and set glfw callback for window resize
  glViewport( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );
  glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

  #pragma endregion


  #pragma region compute shader setup

  Compute compute_shader( "shader.comp", glm::uvec2( 10, 1 ) );

  compute_shader.use();
  float values[ 10 ] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  compute_shader.set_values( values );

  #pragma endregion

  #pragma region rendering setup

  Shader visual_shader( "shader.vert", "shader.frag" );
  BatchRenderer renderer;

  #pragma endregion

  #pragma region render loop

  while ( !glfwWindowShouldClose( window ) ) {
    // input
    // close window on pressing esc
    if ( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS ) {
      glfwSetWindowShouldClose( window, true );
    }

    // update
    compute_shader.use();
    compute_shader.dispatch();
    compute_shader.wait();

    // print data
    /*
    auto data = compute_shader.get_values();
    for ( auto d : data ) {
      std::cout << d << " ";
    }
    std::cout << std::endl;
    */

    // draw
    renderer.clear( glm::vec3( 0.1f, 0.1f, 0.1f ) );

    auto x_offset = glm::sin( glfwGetTime() * 2 ) * 0.2;
    renderer.add_square(
      glm::vec2( 0.0f + x_offset, 0.0f ),
      glm::uvec3( 255, 0, 0 ),
      0.1f );
    renderer.add_square(
      glm::vec2( 0.0f + x_offset, 0.5f ),
      glm::uvec3( 0, 255, 0 ),
      0.1f );
    renderer.add_square(
      glm::vec2( 0.0f + x_offset, -0.5f ),
      glm::uvec3( 0, 0, 255 ),
      0.1f );

    renderer.render( &visual_shader );

    // poll glfw events and swap buffers
    glfwPollEvents();
    glfwSwapBuffers( window );
  }

  #pragma endregion

  // clean up resources upon successful exit
  glfwTerminate();

  return 0;
}
