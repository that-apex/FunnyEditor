#pragma once
#ifndef FUNNYEDITOR_SRC_COMMON_HPP_
#define FUNNYEDITOR_SRC_COMMON_HPP_

#include <exception>
#include <memory>
#include <optional>
#include <string>
#include <utility>

#include <easylogging++.h>

namespace FE {

    class Exception : public std::exception {
    public:
        explicit Exception(std::string what);

        [[nodiscard]] const char * what() const noexcept override;

    private:
        const std::string m_what;
    };

    class NoCopy {
    public:
        NoCopy(const NoCopy &other) = delete;

        NoCopy &operator=(const NoCopy &other) = delete;

    protected:
        NoCopy() = default;
    };

} // namespace FE

#endif //FUNNYEDITOR_SRC_COMMON_HPP_
