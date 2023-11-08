#include "gp/Shader.hpp"
#include <fstream>
#include <sstream>

#include <iostream>

namespace gp {

#define _GP_GEN_CSTR_NAME_ENUM_CASE(v) case v: return #v

const char* to_cstr(const ShaderType& type)
{
    switch (type) {
    _GP_GEN_CSTR_NAME_ENUM_CASE(ShaderType::Vertex);
    _GP_GEN_CSTR_NAME_ENUM_CASE(ShaderType::Fragment);
    _GP_GEN_CSTR_NAME_ENUM_CASE(ShaderType::Geometry);
    _GP_GEN_CSTR_NAME_ENUM_CASE(ShaderType::TessControl);
    _GP_GEN_CSTR_NAME_ENUM_CASE(ShaderType::TessEvaluation);
    _GP_GEN_CSTR_NAME_ENUM_CASE(ShaderType::Compute);
    default: return "ShaderType::Unknown";
    }
}

#undef _OBSVTX_GEN_CSTR_NAME_ENUM_CASE

std::string to_string(const ShaderType& type)
{
    return std::string(to_cstr(type));
}

void Shader::_fromSource(const ShaderType& type, const char *const src)
{
    int success;

    m_id = glCreateShader((GLenum)type);
    glShaderSource(m_id, 1, &src, NULL);
    glCompileShader(m_id);
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(m_id, 512, NULL, infoLog);
        glDeleteShader(m_id);
        throw ShaderException("Error compiling shader of type: " +
                              to_string(type) + ", " + infoLog);
    }
}

void Shader::_fromFilepath(const ShaderType& type, const char *const fp)
{
    std::string content;
    try {
        std::ifstream file(fp);
        if (file.fail())
            throw ShaderException("Error opening shader file: " + std::string(fp));
        std::stringstream ss;
        ss << file.rdbuf();
        content = ss.str();
    } catch (const std::ifstream::failure& e) {
        throw ShaderException("Error reading shader file: " + std::string(e.what()));
    }
    _fromSource(type, content.c_str());
}

Shader::Shader(const ShaderType &type, const char *cptr, const bool &source_is_filepath)
{
    source_is_filepath ? _fromFilepath(type, cptr) : _fromSource(type, cptr);
}

Shader::~Shader()
{
    if (m_id)
        glDeleteShader(m_id);
}

Shader::Shader(Shader&& s) {
    m_id = s.m_id;
    s.m_id = 0;
}

GLuint Shader::id() const { return m_id; }

ShaderException::ShaderException(const std::string &message) :
        Exception(message) {}

} // namespace gp
