#include "SDL.hpp"


namespace FE::SDL {


    SDLException::SDLException(const std::string &prefix) : Exception{prefix + SDL_GetError()} {}

    SDLInit::SDLInit(Uint32 subsystems) : m_subsystems{subsystems} {
        if (SDL_InitSubSystem(m_subsystems) != 0) {
            throw SDLException{"Subsystem init failure"};
        }
    }

    SDLInit::~SDLInit() {
        SDL_QuitSubSystem(m_subsystems);
    }


} // namespace FE::SDL