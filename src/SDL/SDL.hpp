#pragma once
#ifndef FUNNYEDITOR_SRC_FFMPEG_SDLINIT_HPP_
#define FUNNYEDITOR_SRC_FFMPEG_SDLINIT_HPP_

#include "../Common.hpp"
#include <SDL.h>

#define SDL_ASSERT(assertion, prefix) \
    if (!(assertion)) throw FE::SDL::SDLException{prefix};

namespace FE::SDL {

    class SDLException : public Exception {
    public:
        explicit SDLException(const std::string &prefix);
    }; // class SDLException

    class SDLInit : NoCopy {
    public:
        explicit SDLInit(Uint32 subsystems);

        ~SDLInit();

    private:
        Uint32 m_subsystems;
    }; // class SDLInit

    template<typename T>
    using SDLDeleter = void (*)(T *);

    template<typename T>
    using SDLPointer = std::unique_ptr<T, SDLDeleter<T>>;

} // namespace FE::SDL

#endif //FUNNYEDITOR_SRC_FFMPEG_SDLINIT_HPP_
