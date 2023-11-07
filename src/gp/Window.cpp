#include "gp/Window.hpp"

namespace gp {

static bool initialized = false;
static int major_version;
static int minor_version;
static bool core_profile_type;

void initialize_gl_pipeline(int major, int minor, bool core_profile, bool forward_compat, bool vsync) {
    if (initialized) {
        if (major_version != major || minor_version != minor || core_profile_type != core_profile) {
            throw GLInitError("OpenGL pipeline is already initialized with different version or profile");
        }
        return;
    }

    major_version = major;
    minor_version = minor;
    core_profile_type = core_profile;

    if (!glfwInit()) {
        throw GLInitError("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    initialized = true;
}

void terminate_gl_pipeline() {
    if (!initialized) {
        return;
    }
    glfwTerminate();
}

Window::Window(const glm::ivec2 &size, const std::string &title)
    : m_size(size)
    , m_title(title)
    , m_clear_color(0.0f, 0.0f, 0.0f, 1.0f)
{
    if (!initialized) {
        throw GLInitError("OpenGL pipeline is not initialized yet, call gp::initialize_gl_pipeline() first");
    }

    m_window = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
    if (!m_window) {
        const char *error;
        if (glfwGetError(&error) == GLFW_NO_ERROR) {
            error = "Unknown error";
        }
        throw WindowError("Failed to create window because: " + std::string(error));
    }
    glfwMakeContextCurrent(m_window);

    if (gl3wInit() != GL3W_OK) {
        throw WindowError("Failed to initialize OpenGL (gl3w)");
    }

    if (!gl3wIsSupported(4, 2)) {
        throw WindowError("OpenGL " + std::to_string(major_version) + "." +
                                 std::to_string(minor_version) + " is not supported in this system");
    }
}

Window::~Window() {
    glfwDestroyWindow(m_window);
}

void Window::clear() {
    glClearColor(m_clear_color.r, m_clear_color.g, m_clear_color.b, m_clear_color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::display() {
    glfwSwapBuffers(m_window);
}

void Window::poll_events() {
    glfwPollEvents();
}

bool Window::should_close() {
    return glfwWindowShouldClose(m_window);
}

void Window::close() {
    glfwSetWindowShouldClose(m_window, GL_TRUE);
}

void Window::set_clear_color(const glm::vec4 &color) {
    m_clear_color = color;
}

void Window::set_title(const std::string &title) {
    m_title = title;
    glfwSetWindowTitle(m_window, title.c_str());
}

void Window::set_size(const glm::ivec2 &size) {
    m_size = size;
    glfwSetWindowSize(m_window, size.x, size.y);
}

void Window::as_current_context() {
    glfwMakeContextCurrent(m_window);
}

const glm::ivec2 &Window::get_size() const {
    return m_size;
}

const std::string &Window::get_title() const {
    return m_title;
}

GLFWwindow *Window::get_handle() {
    return m_window;
}

void Window::draw(const Drawable &drawable) {
    drawable.draw();
}

GLInitError::GLInitError(const std::string &msg) : Exception(msg) {}

WindowError::WindowError(const std::string &msg) : Exception(msg) {}

} // namespace gp