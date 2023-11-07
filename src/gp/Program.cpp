#include "gp/Program.hpp"

namespace gp {

    Program::Program(const std::vector<Shader>& shaders)
    {
        int success;

        m_id = glCreateProgram();
        for (const Shader& shader : shaders) {
            glAttachShader(m_id, shader.id());
        }
        glLinkProgram(m_id);
        glGetProgramiv(m_id, GL_LINK_STATUS, &success);
        if (!success) {
            char log[512];
            glGetProgramInfoLog(m_id, 512, NULL, log);
            glDeleteProgram(m_id);
            throw ProgramException("Could not link program: " + std::string(log));
        }
    }

    Program::~Program()
    {
        if (m_id != GL_ZERO && m_rc.count() == 1) {
            glDeleteProgram(m_id);
        }
    }

    Program::Program(Program&& other) :
        m_id(other.m_id)
        , m_uniform_cache(std::move(other.m_uniform_cache))
        , m_rc(std::move(other.m_rc))
    {
        other.m_id = GL_ZERO;
    }

    Program& Program::use()
    {
        glUseProgram(m_id);
        return *this;
    }

    void Program::unuse()
    {
        glUseProgram(GL_ZERO);
    }

    GLint Program::getUniform(const std::string& uniform)
    {
        auto it = m_uniform_cache.find(uniform);
        if (it == m_uniform_cache.end()) {
            GLint vuniform = glGetUniformLocation(m_id, uniform.c_str());
            if (vuniform == -1) {
                throw ProgramException("Could not find uniform: " + uniform);
            }
            m_uniform_cache[uniform] = vuniform;
            return vuniform;
        }
        return it->second;
    }


#define _OBSVTX_DECLARE_SET_UNIFORM_ANY(value_type) \
    template<> \
    Program& Program::setUniform<value_type>(const std::string& uniform, const value_type& value) { \
        return setUniform(getUniform(uniform), value); \
    }

#define _OBSVTX_DECLARE_SET_UNIFORM_MAT(value_type, method) \
    template<> \
    Program& Program::setUniform<value_type>(GLint uniform, const value_type& value) { \
        method(uniform, 1, GL_FALSE, glm::value_ptr(value)); \
        return *this; \
    } \
    _OBSVTX_DECLARE_SET_UNIFORM_ANY(value_type)

#define _OBSVTX_DECLARE_SET_UNIFORM_VEC(value_type, method) \
    template<> \
    Program& Program::setUniform<value_type>(GLint uniform, const value_type& value) { \
        method(uniform, 1, glm::value_ptr(value)); \
        return *this; \
    } \
    _OBSVTX_DECLARE_SET_UNIFORM_ANY(value_type)

#define _OBSVTX_DECLARE_SET_UNIFORM_SCALAR(value_type, method) \
    template<> \
    Program& Program::setUniform<value_type>(GLint uniform, const value_type& value) { \
        method(uniform, value); \
        return *this; \
    } \
    _OBSVTX_DECLARE_SET_UNIFORM_ANY(value_type)

    _OBSVTX_DECLARE_SET_UNIFORM_SCALAR(GLbyte, glUniform1i);
    _OBSVTX_DECLARE_SET_UNIFORM_SCALAR(GLubyte, glUniform1ui);
    _OBSVTX_DECLARE_SET_UNIFORM_SCALAR(GLshort, glUniform1i);
    _OBSVTX_DECLARE_SET_UNIFORM_SCALAR(GLint, glUniform1i);
    _OBSVTX_DECLARE_SET_UNIFORM_SCALAR(GLuint, glUniform1ui);
    _OBSVTX_DECLARE_SET_UNIFORM_SCALAR(GLfloat, glUniform1f);
    _OBSVTX_DECLARE_SET_UNIFORM_SCALAR(GLdouble, glUniform1d);

    _OBSVTX_DECLARE_SET_UNIFORM_VEC(glm::vec2, glUniform2fv);
    _OBSVTX_DECLARE_SET_UNIFORM_VEC(glm::vec3, glUniform3fv);
    _OBSVTX_DECLARE_SET_UNIFORM_VEC(glm::vec4, glUniform4fv);

    _OBSVTX_DECLARE_SET_UNIFORM_VEC(glm::ivec2, glUniform2iv);
    _OBSVTX_DECLARE_SET_UNIFORM_VEC(glm::ivec3, glUniform3iv);
    _OBSVTX_DECLARE_SET_UNIFORM_VEC(glm::ivec4, glUniform4iv);

    _OBSVTX_DECLARE_SET_UNIFORM_VEC(glm::uvec2, glUniform2uiv);
    _OBSVTX_DECLARE_SET_UNIFORM_VEC(glm::uvec3, glUniform3uiv);
    _OBSVTX_DECLARE_SET_UNIFORM_VEC(glm::uvec4, glUniform4uiv);

    _OBSVTX_DECLARE_SET_UNIFORM_MAT(glm::mat2, glUniformMatrix2fv);
    _OBSVTX_DECLARE_SET_UNIFORM_MAT(glm::mat3, glUniformMatrix3fv);
    _OBSVTX_DECLARE_SET_UNIFORM_MAT(glm::mat4, glUniformMatrix4fv);

    _OBSVTX_DECLARE_SET_UNIFORM_MAT(glm::dmat2, glUniformMatrix2dv);
    _OBSVTX_DECLARE_SET_UNIFORM_MAT(glm::dmat3, glUniformMatrix3dv);
    _OBSVTX_DECLARE_SET_UNIFORM_MAT(glm::dmat4, glUniformMatrix4dv);

    _OBSVTX_DECLARE_SET_UNIFORM_MAT(glm::mat2x3, glUniformMatrix2x3fv);
    _OBSVTX_DECLARE_SET_UNIFORM_MAT(glm::mat3x2, glUniformMatrix3x2fv);
    _OBSVTX_DECLARE_SET_UNIFORM_MAT(glm::mat2x4, glUniformMatrix2x4fv);
    _OBSVTX_DECLARE_SET_UNIFORM_MAT(glm::mat4x2, glUniformMatrix4x2fv);
    _OBSVTX_DECLARE_SET_UNIFORM_MAT(glm::mat3x4, glUniformMatrix3x4fv);
    _OBSVTX_DECLARE_SET_UNIFORM_MAT(glm::mat4x3, glUniformMatrix4x3fv);

    _OBSVTX_DECLARE_SET_UNIFORM_MAT(glm::dmat2x3, glUniformMatrix2x3dv);
    _OBSVTX_DECLARE_SET_UNIFORM_MAT(glm::dmat3x2, glUniformMatrix3x2dv);
    _OBSVTX_DECLARE_SET_UNIFORM_MAT(glm::dmat2x4, glUniformMatrix2x4dv);
    _OBSVTX_DECLARE_SET_UNIFORM_MAT(glm::dmat4x2, glUniformMatrix4x2dv);
    _OBSVTX_DECLARE_SET_UNIFORM_MAT(glm::dmat3x4, glUniformMatrix3x4dv);
    _OBSVTX_DECLARE_SET_UNIFORM_MAT(glm::dmat4x3, glUniformMatrix4x3dv);

#undef _OBSVTX_DECLARE_SET_UNIFORM_SCALAR
#undef _OBSVTX_DECLARE_SET_UNIFORM_VEC
#undef _OBSVTX_DECLARE_SET_UNIFORM_MAT
#undef _OBSVTX_DECLARE_SET_UNIFORM_ANY

    ProgramBuilder &ProgramBuilder::addShader(const ShaderType& type, const char* const cptr, const bool &is_filepath) {
        m_shaders.emplace_back(type, cptr, is_filepath);
        return *this;
    }

    Program ProgramBuilder::build() {
        return Program(m_shaders);
    }

    std::unique_ptr<Program> ProgramBuilder::build_unique() {
        return std::make_unique<Program>(m_shaders);
    }

    std::shared_ptr<Program> ProgramBuilder::build_shared() {
        return std::make_shared<Program>(m_shaders);
    }

    ProgramException::ProgramException(const std::string message)
        : Exception(message)
    {}

}
