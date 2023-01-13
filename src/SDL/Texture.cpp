#include "Texture.hpp"

#include <iostream>

namespace FE::SDL {

    Texture::Texture(SDL_Renderer *renderer, Uint32 format, int access, int width, int height) {
        m_texture.reset(SDL_CreateTexture(renderer, format, access, width, height));
        SDL_ASSERT(m_texture, "Failed to create texture: ");
    }

    SDL_Texture &Texture::GetTexture() noexcept {
        return *m_texture.get();
    }

    void Texture::UpdateYUV(const SDL_Rect *rect, const Uint8 *Yplane, int Ypitch, const Uint8 *Uplane, int Upitch,
                            const Uint8 *Vplane, int Vpitch) {

        int err = SDL_UpdateYUVTexture(m_texture.get(), rect, Yplane, Ypitch, Uplane, Upitch, Vplane, Vpitch);
        SDL_ASSERT(err == 0, "SDL_UpdateYUVTexture failed");
    }

} // namespace FE::SDL