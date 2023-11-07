#pragma once

#include "Other/GL.h"
#include "RC.hpp"
#include "Error.hpp"

namespace gp {
namespace glObject {

    class glObjectException : public Exception {
    public:
        glObjectException(const std::string &message) : Exception(message) {}
    };

    #define _OBSVTX_GENERATE_AUTO_SINGLE_GL_OBJECT(CLASS_NAME, INITIALIZER, DELETER, INITIALIZER_ERROR_MESSAGE) \
    class CLASS_NAME { \
    private: \
        RC m_rc; \
        GLuint m_object; \
    public: \
        CLASS_NAME() : m_object(0) { \
            INITIALIZER(1, &m_object); \
            if (m_object == 0) \
                throw glObjectException(INITIALIZER_ERROR_MESSAGE); \
        } \
        CLASS_NAME(const CLASS_NAME& other) = default; \
        CLASS_NAME(CLASS_NAME&& other) = default; \
        ~CLASS_NAME() { \
            if (m_object != 0 && m_rc.count() == 1) \
                DELETER(1, &m_object); \
        } \
        GLuint get() const { return m_object; } \
        GLuint operator*() const { return m_object; } \
    }

    _OBSVTX_GENERATE_AUTO_SINGLE_GL_OBJECT(AutoVao, glGenVertexArrays, glDeleteVertexArrays, "Failed to create VAO");
    _OBSVTX_GENERATE_AUTO_SINGLE_GL_OBJECT(AutoVbo, glGenBuffers, glDeleteBuffers, "Failed to create VBO");
    _OBSVTX_GENERATE_AUTO_SINGLE_GL_OBJECT(AutoEbo, glGenBuffers, glDeleteBuffers, "Failed to create EBO");
    _OBSVTX_GENERATE_AUTO_SINGLE_GL_OBJECT(AutoTexture, glGenTextures, glDeleteTextures, "Failed to create texture");
    _OBSVTX_GENERATE_AUTO_SINGLE_GL_OBJECT(AutoFramebuffer, glGenFramebuffers, glDeleteFramebuffers, "Failed to create framebuffer");
    _OBSVTX_GENERATE_AUTO_SINGLE_GL_OBJECT(AutoRenderbuffer, glGenRenderbuffers, glDeleteRenderbuffers, "Failed to create renderbuffer");
    _OBSVTX_GENERATE_AUTO_SINGLE_GL_OBJECT(AutoSampler, glGenSamplers, glDeleteSamplers, "Failed to create sampler");
    _OBSVTX_GENERATE_AUTO_SINGLE_GL_OBJECT(AutoTransformFeedback, glGenTransformFeedbacks, glDeleteTransformFeedbacks, "Failed to create transform feedback");
    _OBSVTX_GENERATE_AUTO_SINGLE_GL_OBJECT(AutoProgramPipeline, glGenProgramPipelines, glDeleteProgramPipelines, "Failed to create program pipeline");

    #undef _OBSVTX_GENERATE_AUTO_SINGLE_GL_OBJECT

    inline void bind(const AutoVao& obj) {
        glBindVertexArray(obj.get());
    }
    inline void unbind(const AutoVao& obj) {
        glBindVertexArray(0);
    }

    inline void bind(const AutoVbo& obj) {
        glBindBuffer(GL_ARRAY_BUFFER, obj.get());
    }

    inline void unbind(const AutoVbo& obj) {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    inline void bind(const AutoEbo& obj) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.get());
    }

    inline void unbind(const AutoEbo& obj) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    inline void bind(const AutoTexture& obj) {
        glBindTexture(GL_TEXTURE_2D, obj.get());
    }

    inline void unbind(const AutoTexture& obj) {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    inline void bind(const AutoFramebuffer& obj) {
        glBindFramebuffer(GL_FRAMEBUFFER, obj.get());
    }

    inline void unbind(const AutoFramebuffer& obj) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    inline void bind(const AutoRenderbuffer& obj) {
        glBindRenderbuffer(GL_RENDERBUFFER, obj.get());
    }

    inline void unbind(const AutoRenderbuffer& obj) {
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    inline void bind(const AutoSampler& obj) {
        glBindSampler(0, obj.get());
    }

    inline void unbind(const AutoSampler& obj) {
        glBindSampler(0, 0);
    }

    inline void bind(const AutoTransformFeedback& obj) {
        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, obj.get());
    }

    inline void unbind(const AutoTransformFeedback& obj) {
        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
    }

    inline void bind(const AutoProgramPipeline& obj) {
        glBindProgramPipeline(obj.get());
    }

    inline void unbind(const AutoProgramPipeline& obj) {
        glBindProgramPipeline(0);
    }
}
}
