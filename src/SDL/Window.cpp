#include "Window.hpp"

namespace FE::SDL {

    Window::Window(std::string title, int x, int y, int width, int height, Uint32 windowFlags, Uint32 rendererFlags)
            : m_title{std::move(title)}, m_x{x}, m_y{y}, m_width{width}, m_height{height}, m_windowFlags{windowFlags},
              m_rendererFlags{rendererFlags} {

        m_window.reset(SDL_CreateWindow(m_title.c_str(), m_x, m_y, m_width, m_height, m_windowFlags));
        SDL_ASSERT(m_window, "Failed to create window: ");

        m_renderer.reset(SDL_CreateRenderer(m_window.get(), -1, m_rendererFlags));
        SDL_ASSERT(m_renderer, "Failed to create renderer: ");
    }

    [[nodiscard]] SDL_Window &Window::GetWindow() noexcept {
        return *m_window.get();
    }

    [[nodiscard]] SDL_Renderer &Window::GetRenderer() noexcept {
        return *m_renderer.get();
    }

    Texture Window::CreateTexture(Uint32 format, int access, int width, int height) {
        return {m_renderer.get(), format, access, width, height};
    }

    void Window::RenderCopy(Texture& texture, const SDL_Rect *srcRec, const SDL_Rect *dstRec) {
        SDL_RenderCopy(m_renderer.get(), &texture.GetTexture(), srcRec, dstRec);
    }

    void Window::RenderPresent() {
        SDL_RenderPresent(m_renderer.get());
    }

    void Window::UpdateSurface() {
        SDL_UpdateWindowSurface(m_window.get());
    }

} // namespace FE::SDL