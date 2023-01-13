#pragma once
#ifndef FUNNYEDITOR_SRC_VIDEO_RENDERER_HPP_
#define FUNNYEDITOR_SRC_VIDEO_RENDERER_HPP_

#include "../Common.hpp"
#include "../SDL/Window.hpp"
#include "../SDL/Texture.hpp"
#include "../FFmpeg/CodecContext.hpp"
#include "../FFmpeg/Frame.hpp"
#include "../FFmpeg/Packet.hpp"
#include "../FFmpeg/Stream.hpp"

namespace FE::Video {

    class Renderer {
    public:
        Renderer(SDL::Texture texture, FFmpeg::VideoStream videoStream,FFmpeg::CodecContext decoderContext);

    public:
        bool HandlePacket(FFmpeg::Packet& packet);

        SDL::Texture &GetTexture();

    public:
        static Renderer Create(SDL::Window& window, FFmpeg::VideoStream videoStream);

    private:
        SDL::Texture m_texture;
        FFmpeg::VideoStream m_videoStream;
        FFmpeg::CodecContext m_decoderContext;
        FFmpeg::Frame m_frame;
        int m_videoStreamIndex;

    }; // class Renderer

} // namespace FE::Video

#endif //FUNNYEDITOR_SRC_VIDEO_RENDERER_HPP_
