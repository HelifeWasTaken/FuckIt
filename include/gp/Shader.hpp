#pragma once

#include "Other/GL.h"
#include "Error.hpp"

namespace gp {

    // Differents available shader types
    enum class ShaderType : GLenum {
        Vertex = GL_VERTEX_SHADER,
        Fragment = GL_FRAGMENT_SHADER,
        Geometry = GL_GEOMETRY_SHADER,
        TessControl = GL_TESS_CONTROL_SHADER,
        TessEvaluation = GL_TESS_EVALUATION_SHADER,
        Compute = GL_COMPUTE_SHADER
    };

    // transform a shader type to cstr
    const char* to_cstr(const ShaderType& type);

    // transform a shader type to string
    std::string to_string(const ShaderType& type);

    // Object abstraction of the Shader GL object
    class Shader {
    private:
        GLuint m_id;

        // Compile a shader from source
        void _fromSource(const ShaderType& type, const char *const src);

        // Compile a shader from a filepath
        void _fromFilepath(const ShaderType& type, const char *const fp);

    public:
        // Make a new shader object
        // cptr is either the source code or the filepath depeding of the 3rd argument
        Shader(const ShaderType &type, const char *const cptr, const bool &cptr_is_filepath);

        // Destroys the shader object
        ~Shader();

        // Disallow copy
        Shader(const Shader& s) = delete;
        // Allow move
        Shader(Shader&& s);
        // Returns the GL handle of the Shader
        GLuint id() const;
    };

    // Base class for all shader exceptions
    class ShaderException : public Exception {
    public:
        ShaderException(const std::string &message);
    };
}
