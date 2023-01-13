#include "Common.hpp"

namespace FE {
    Exception::Exception(std::string what) : m_what{std::move(what)} {
    }

    const char *Exception::what() const noexcept {
        return m_what.c_str();
    }
}