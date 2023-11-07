#pragma once

#include "Other/GL.h"
#include "Error.hpp"
#include "Drawable.hpp"
#include <string>

namespace gp {

class Window {
private:
    GLFWwindow *m_window;
    glm::vec4 m_clear_color;
    glm::ivec2 m_size;
    std::string m_title;

public:
    Window(const glm::ivec2 &size, const std::string &title);
    ~Window();

    void clear();
    void display();
    void poll_events();
    bool should_close();
    void close();
    void set_clear_color(const glm::vec4 &color);
    void set_title(const std::string &title);
    void set_size(const glm::ivec2 &size);
    void as_current_context();

    const glm::ivec2 &get_size() const;
    const std::string &get_title() const;

    GLFWwindow *get_handle();

    void draw(const Drawable &drawable);
};

class GLInitError : public Exception {
public:
    GLInitError(const std::string &msg);
};

class WindowError : public Exception {
public:
    WindowError(const std::string &msg);
};

#define GP_DEFAULT_MAJOR_VERSION 4
#define GP_DEFAULT_MINOR_VERSION 3
#define GP_DEFAULT_CORE_PROFILE true
#define GP_DEFAULT_FORWARD_COMPAT true
#define GP_DEFAULT_VSYNC true

void initialize_gl_pipeline(int major=GP_DEFAULT_MAJOR_VERSION,
                            int minor=GP_DEFAULT_MINOR_VERSION,
                            bool core_profile=true,
                            bool forward_compat=false,
                            bool vsync=true);
void terminate_gl_pipeline();

} // namespace gp
