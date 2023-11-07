#pragma once

#include "Shader.hpp"
#include "RC.hpp"

#include <vector>
#include <memory>
#include <unordered_map>
#include <atomic>

namespace gp {

    class Program {
    private:
        GLuint m_id;
        std::unordered_map<std::string, GLint> m_uniform_cache;
        mutable RC m_rc;

    public:
        // Constructor of the shader
        Program(const std::vector<Shader>& shaders);
        // destructor of the Shader
        ~Program();
        // disallow copy
        Program(const Program&) = default;
        // disallow move
        Program(Program&&);

        // use the program
        Program& use();
        // unuse program
        void unuse();

        // Gets the uniform location
        GLint getUniform(const std::string& uniform);

        // Sets the uniform value
        template<typename T>
        Program& setUniform(const std::string& uniform, const T& value);

        // Sets the uniform value
        template<typename T>
        Program& setUniform(GLint uniform, const T& value);
    };

    // Helper class to build a GLSL Program
    class ProgramBuilder {
    private:
        std::vector<Shader> m_shaders;

    public:
        // default constructor
        ProgramBuilder() = default;
        // default destructor
        ~ProgramBuilder() = default;
        // disallow copy
        ProgramBuilder(const ProgramBuilder&) = delete;
        // disallow move
        ProgramBuilder(ProgramBuilder&&) = delete;

        // Adds a program base on the argument that satisfies the Shader constructor
        ProgramBuilder &addShader(const ShaderType& type, const char* const cptr, const bool &is_filepath);

        // Build the program class
        Program build();

        // Build the program class in a unique ptr wrapper
        std::unique_ptr<Program> build_unique();

        // Build the program class in a shared ptr wrapper
        std::shared_ptr<Program> build_shared();
    };

    // Base program exception class
    class ProgramException : public Exception {
    public:
        ProgramException(const std::string message);
    };
}