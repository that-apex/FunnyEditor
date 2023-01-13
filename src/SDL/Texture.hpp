#pragma once
#ifndef FUNNYEDITOR_SRC_SDL_TEXTURE_HPP_
#define FUNNYEDITOR_SRC_SDL_TEXTURE_HPP_

#include "SDL.hpp"
#include <memory>

namespace FE::SDL {

    class Texture {
    public:
        Texture(SDL_Renderer *renderer, Uint32 format, int access, int width, int height);

    public:
        [[nodiscard]] SDL_Texture &GetTexture() noexcept;

        void UpdateYUV(
                const SDL_Rect *rect,
                const Uint8 *Yplane, int Ypitch,
                const Uint8 *Uplane, int Upitch,
                const Uint8 *Vplane, int Vpitch
        );

    private:
        SDLPointer<SDL_Texture> m_texture{nullptr, &SDL_DestroyTexture};

    }; // class Texture

} // namespace FE::SDL

#endif //FUNNYEDITOR_SRC_SDL_TEXTURE_HPP_
