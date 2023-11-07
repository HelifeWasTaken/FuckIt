#pragma once

#include "Other/GL.h"

namespace gp {

    class Camera {
        public:
            Camera(const glm::vec3 &pos, const glm::vec3 &lookAt, const glm::vec3 &up, float fov, float aspectRatio);
            glm::mat4 getViewMatrix() const;
            glm::mat4 getProjectionMatrix() const;
            glm::vec3 getPosition() const;
            glm::vec3 getLookAt() const;
            glm::vec3 getUp() const;
            float getFov() const;
            float getAspectRatio() const;
            void setPosition(const glm::vec3 &pos);
            void setLookAt(const glm::vec3 &lookAt);
            void setUp(const glm::vec3 &up);
            void setFov(float fov);
            void setAspectRatio(float aspectRatio);
        private:
            glm::vec3 m_pos;
            glm::vec3 m_lookAt;
            glm::vec3 m_up;
            float m_fov;
            float m_aspectRatio;
    };

}