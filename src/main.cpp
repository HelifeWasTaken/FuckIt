#include "gp/Window.hpp"
#include "gp/Program.hpp"
#include "gp/glObject.hpp"
#include <vector>
#include "gp/Drawable.hpp"
#include "gp/Camera.hpp"

#include <iostream>

int main() {
    gp::initialize_gl_pipeline();

    gp::Window window({ 800, 800 }, "Hello, world!");
    glfwSwapInterval(1);
    window.set_clear_color({ 0.2f, 0.3f, 0.3f, 1.0f });
    //glEnable(GL_DEPTH_TEST);

    gp::CubeRough cuboid;
    // gp::Triangle triangle(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

    while (!window.should_close()) {
        //window.clear();
        window.draw(cuboid);
        window.display();
        window.poll_events();
    }

    gp::terminate_gl_pipeline();
    return 0;
}