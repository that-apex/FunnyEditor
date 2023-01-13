#pragma once
#ifndef FUNNYEDITOR_SRC_SDL_WINDOW_HPP_
#define FUNNYEDITOR_SRC_SDL_WINDOW_HPP_

#include "SDL.hpp"
#include "Texture.hpp"

namespace FE::SDL {

    class Window : NoCopy {
    public:
        Window(std::string title, int x, int y, int width, int height, Uint32 windowFlags = 0,
               Uint32 rendererFlags = 0);

    public:
        [[nodiscard]] SDL_Window& GetWindow() noexcept;

        [[nodiscard]] SDL_Renderer& GetRenderer() noexcept;

        [[nodiscard]] Texture CreateTexture(Uint32 format, int access, int width, int height);

        void RenderCopy(Texture& texture, const SDL_Rect *srcRec, const SDL_Rect *dstRec);

        void RenderPresent();

        void UpdateSurface();

    private:
        std::string m_title;
        int m_x;
        int m_y;
        int m_width;
        int m_height;
        Uint32 m_windowFlags;
        Uint32 m_rendererFlags;

        SDLPointer<SDL_Window> m_window{nullptr, &SDL_DestroyWindow};
        SDLPointer<SDL_Renderer> m_renderer{nullptr, &SDL_DestroyRenderer};

    }; // class Window

} // namespace FE::SDL

#endif //FUNNYEDITOR_SRC_SDL_WINDOW_HPP_
