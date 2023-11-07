#include "gp/RC.hpp"

namespace gp {

    RC::RC() : m_count(new RcValue(1)) {}

    // Copy constructor
    RC::RC(const RC& other) : m_count(other.m_count) 
    {
        if (m_count != nullptr) {
            ++(*m_count);
        } else {
            m_count = new RcValue(1);
        }
    }

    // Move constructor
    RC::RC(RC&& other) : m_count(other.m_count)
    { 
        other.m_count = nullptr;
    }

    // Destructor
    RC::~RC() {
        if (m_count != nullptr && --(*m_count) == 0)
            delete m_count;
    }

    // Current reference count
    RcValue RC::count() const { return m_count ? *m_count : 0; }
}