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

    gp::Cuboid cuboid;

    std::shared_ptr<gp::Program> m_program;
    gp::ProgramBuilder builder;
    builder.addShader(gp::ShaderType::Vertex, "../assets/shaders/simple.vert", true)
        .addShader(gp::ShaderType::Fragment, "../assets/shaders/simple.frag", true);
    m_program = builder.build_shared();

    glm::mat4 projection = glm::perspective(45.0f, 1.0f, 0.1f, 500.f);
    glm::mat4 view = glm::lookAt(glm::vec3(5, 5, 5), glm::vec3(0.f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 model = glm::rotate(glm::mat4(1.0f), 10.0f, glm::vec3(1.0f, 0.0f, 0.0f));

    m_program->use();
    m_program->setUniform("viewMatrix", projection)
        .setUniform("projectionMatrix", view)
        .setUniform("modelMatrix", model);

    while (!window.should_close()) {
        window.clear();
        m_program->use();
        window.draw(cuboid);
        m_program->unuse();
        window.display();
        window.poll_events();
    }

    gp::terminate_gl_pipeline();
    return 0;
}