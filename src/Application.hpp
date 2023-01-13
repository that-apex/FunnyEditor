#pragma once
#ifndef FUNNYEDITOR_SRC_APPLICATION_HPP_
#define FUNNYEDITOR_SRC_APPLICATION_HPP_

#include "Common.hpp"

namespace FE {

    class Application : NoCopy {
    public:
        Application(int argc, char **argv);

    public:
        int Run();

    private:
        int m_argc;
        char **m_argv;
    };

} // namespace FE

#endif //FUNNYEDITOR_SRC_APPLICATION_HPP_
