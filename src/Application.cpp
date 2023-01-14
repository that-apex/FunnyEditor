#include "Application.hpp"

#include <iostream>

#include "FFmpeg/CodecContext.hpp"
#include "FFmpeg/FormatContext.hpp"
#include "FFmpeg/Frame.hpp"
#include "FFmpeg/FrameBuffer.hpp"
#include "FFmpeg/Packet.hpp"
#include "FFmpeg/Stream.hpp"
#include "SDL/SDL.hpp"
#include "SDL/Texture.hpp"
#include "SDL/Window.hpp"
#include "Video/Renderer.hpp"

INITIALIZE_EASYLOGGINGPP

namespace FE {

    Application::Application(int argc, char **argv) : m_argc{argc}, m_argv{argv} {
    }

    int Application::Run() {
        using namespace std::string_literals;
        LOG(INFO) << "App is starting";

        if (m_argc < 2) {
            LOG(ERROR) << "Usage: "s << m_argv[0] << " <file path>";
            return 1;
        }

        std::string filePath = m_argv[1];

        SDL::SDLInit sdlInit{SDL_INIT_VIDEO};
        SDL::Window window{"FunnyEditor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080};

        FFmpeg::FormatContext formatContext{};
        formatContext.Open(filePath);

        FFmpeg::VideoStream *videoStream = formatContext.FindVideoStream();

        if (videoStream == nullptr)
            throw Exception("no videoStream");

        Video::Renderer renderer = Video::Renderer::Create(window, *videoStream);
        FFmpeg::Packet packet;
        SDL_Event evt;

        while (true) {
            formatContext.ReadPacket(packet);

            renderer.HandlePacket(packet);

            window.RenderCopy(renderer.GetTexture(), nullptr, nullptr);
            window.RenderPresent();
            window.UpdateSurface();

            packet.Unref();

            SDL_PollEvent(&evt);

            switch (evt.type) {
                case SDL_QUIT:
                    goto quit;
                default:
                    break;
            }
        }

        quit:
        return 0;
    }

} // namespace FE