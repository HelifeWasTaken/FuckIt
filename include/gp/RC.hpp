#pragma once

namespace gp {

    using RcValue = unsigned long long;

    // Light wheight reference counting class 
    class RC {
    private:
        mutable RcValue *m_count;
    
    public:
        RC();
        RC(const RC& other);
        RC(RC&& other);
        ~RC();
        RcValue count() const;
    };
}