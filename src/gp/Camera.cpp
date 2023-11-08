#include "gp/Camera.hpp"

namespace gp {

Camera::Camera(const glm::vec3 &pos, const glm::vec3 &lookAt, const glm::vec3 &up, float fov, float aspectRatio) :
    m_pos(pos), m_lookAt(lookAt), m_up(up), m_fov(fov), m_aspectRatio(aspectRatio) {}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(m_pos, m_lookAt, m_up);
}

glm::mat4 Camera::getProjectionMatrix() const {
    return glm::perspective(m_fov, m_aspectRatio, 0.1f, 100.0f);
}

glm::vec3 Camera::getPosition() const {
    return m_pos;
}

glm::vec3 Camera::getLookAt() const {
    return m_lookAt;
}

glm::vec3 Camera::getUp() const {
    return m_up;
}

float Camera::getFov() const {
    return m_fov;
}

float Camera::getAspectRatio() const {
    return m_aspectRatio;
}

void Camera::setPosition(const glm::vec3 &pos) {
    m_pos = pos;
}

void Camera::setLookAt(const glm::vec3 &lookAt) {
    m_lookAt = lookAt;
}

void Camera::setUp(const glm::vec3 &up) {
    m_up = up;
}

void Camera::setFov(float fov) {
    m_fov = fov;
}

void Camera::setAspectRatio(float aspectRatio) {
    m_aspectRatio = aspectRatio;
}

} // namespace gp

