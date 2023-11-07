#pragma once

#include <exception>
#include <string>

namespace gp {

    // Base exception class for all the obsvtx exception
    class Exception : public std::exception {
    private:
        const std::string m_message;

    public:
        Exception(const std::string& message);
        const char *what() const noexcept;
    };

}