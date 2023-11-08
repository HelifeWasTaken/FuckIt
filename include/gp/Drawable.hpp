#pragma once

#include "glObject.hpp"
#include "Other/Utils.h"
#include <array>
#include <iostream>
#include "gp/Program.hpp"

namespace gp {

    class Drawable {
        public:
            virtual void draw() const = 0;
    };

    class Triangle : public Drawable {
    private:
        gp::glObject::AutoVao m_vao;
        gp::glObject::AutoVbo m_vbo_vertices;
        gp::glObject::AutoVbo m_vbo_colors;
        gp::glObject::AutoEbo m_ebo;
        
        static constexpr GLfloat m_vertices[4 * 3] = {
            -0.5f, -0.5f, 0.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 1.0f
        };
        static constexpr GLuint m_indices[3] = {
            0, 1, 2
        };

        GLfloat m_colors[4 * 3];

    public:
        Triangle(glm::vec4 color1, glm::vec4 color2, glm::vec4 color3) {
            std::memcpy(m_colors, glm::value_ptr(color1), sizeof(glm::vec4));
            std::memcpy(m_colors + 4, glm::value_ptr(color2), sizeof(glm::vec4));
            std::memcpy(m_colors + 8, glm::value_ptr(color3), sizeof(glm::vec4));

            gp::glObject::bind(m_vao);
            gp::glObject::bind(m_vbo_vertices);
            glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(0);

            gp::glObject::bind(m_vbo_colors);
            glBufferData(GL_ARRAY_BUFFER, sizeof(m_colors), m_colors, GL_STATIC_DRAW);
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(1);

            gp::glObject::bind(m_ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices, GL_STATIC_DRAW);

            gp::glObject::unbind(m_vao);
            gp::glObject::unbind(m_vbo_vertices);
            gp::glObject::unbind(m_vbo_colors);
        }

        ~Triangle() = default;

        void draw() const override {
            gp::glObject::bind(m_vao);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
            gp::glObject::unbind(m_vao);
        }
    };

    class Cuboid : public Drawable {
    private:
        static constexpr GLfloat m_vertices[] = {
            -1.0f, -1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f, 1.0f,
            1.0f,  1.0f, 1.0f, 1.0f,
            -1.0f,  1.0f, 1.0f, 1.0f,

            -1.0f, -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, -1.0f, 1.0f,
            1.0f,  1.0f, -1.0f, 1.0f,
            -1.0f,  1.0f, -1.0f, 1.0f
        };

        static constexpr GLuint m_indices[] = {
            0, 1, 2,
            2, 3, 0,

            1, 5, 6,
            6, 2, 1,

            7, 6, 5,
            5, 4, 7,

            4, 0, 3,
            3, 7, 4,

            4, 5, 1,
            1, 0, 4,

            3, 2, 6,
            6, 7, 3
        };
        
        gp::glObject::AutoVao m_vao;
        gp::glObject::AutoVbo m_vbo_vertices;
        gp::glObject::AutoVbo m_vbo_colors;
        gp::glObject::AutoEbo m_ebo;

        GLfloat m_colors[GP_ARRAY_SIZE(m_vertices)] = {
            1.0, 0.0, 0.0, 1.0,
            0.0, 1.0, 0.0, 1.0,
            0.0, 0.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0,

            1.0, 0.0, 0.0, 1.0,
            0.0, 1.0, 0.0, 1.0,
            0.0, 0.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0
        };
    
    public:
        Cuboid() {
            gp::glObject::bind(m_vao);

            gp::glObject::bind(m_vbo_vertices);
            glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(0);

            gp::glObject::bind(m_vbo_colors);
            glBufferData(GL_ARRAY_BUFFER, sizeof(m_colors), m_colors, GL_STATIC_DRAW);
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(1);

            gp::glObject::bind(m_ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices, GL_STATIC_DRAW);

            gp::glObject::unbind(m_vao);
            //gp::glObject::unbind(m_ebo);
        }

        ~Cuboid() = default;

        void draw() const override {
            gp::glObject::bind(m_vao);
            glDrawElements(GL_TRIANGLES, GP_ARRAY_SIZE(m_indices), GL_UNSIGNED_INT, nullptr);
            gp::glObject::unbind(m_vao);
        }
    };

    class CubeRough : public Drawable {
    private:
        static constexpr GLfloat m_vertices[] = {
            -1.0f, -1.0f, 1.0,
            1.0f, -1.0f, 1.0f,
            1.0f,  1.0f, 1.0f,
            -1.0f,  1.0f, 1.0f,

            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
        };

        static constexpr GLfloat m_vertex_colors[] = {
            1.0f, 0.0f, 0.0f,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 1.0, 1.0,

            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 1.0, 1.0,
        };

        static constexpr GLushort m_indices[] = {
            0, 1, 2,  2, 3, 0,  1, 5, 6,
            6, 2, 1,  7, 6, 5,  5, 4, 7,
            4, 0, 3,  3, 7, 4,  4, 5, 1,
            1, 0, 4,  3, 2, 6,  6, 7, 3
        };

        GLuint m_vao;
        GLuint m_vbo_vertices;
        GLuint m_vbo_colors;
        GLuint m_ibo;

        std::shared_ptr<Program> m_program;

    public:
        CubeRough()
        {
            glGenVertexArrays(1, &m_vao);
            glBindVertexArray(m_vao);

            glGenBuffers(1, &m_vbo_vertices);
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertices);
            glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(0);

            glGenBuffers(1, &m_vbo_colors);
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo_colors);
            glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertex_colors), m_vertex_colors, GL_STATIC_DRAW);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(1);

            glGenBuffers(1, &m_ibo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices, GL_STATIC_DRAW);

            glBindVertexArray(0);

            gp::ProgramBuilder builder;
            builder.addShader(gp::ShaderType::Vertex, "../assets/shaders/simple.vert", true)
                    .addShader(gp::ShaderType::Fragment, "../assets/shaders/simple.frag", true);
            m_program = builder.build_shared();
        }

        ~CubeRough()
        {
            glDeleteBuffers(1, &m_ibo);
            glDeleteBuffers(1, &m_vbo_colors);
            glDeleteBuffers(1, &m_vbo_vertices);
            glDeleteVertexArrays(1, &m_vao);
        }

        void draw() const override
        {
            glViewport(0, 0, 800, 800);
            m_program->use();
            glBindVertexArray(m_vao);
            int size;
            glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
            glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
            m_program->unuse();
        }
    };
}