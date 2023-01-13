#pragma once
#ifndef FUNNYEDITOR_SRC_FFMPEG_FRAMEBUFFER_HPP_
#define FUNNYEDITOR_SRC_FFMPEG_FRAMEBUFFER_HPP_

#include "FFmpeg.hpp"

namespace FE::FFmpeg {

    class FrameBuffer : NoCopy {
    public:
        FrameBuffer(AVPixelFormat pixelFormat, int width, int height);

        [[nodiscard]] uint8_t *Data() noexcept;

        [[nodiscard]] const uint8_t *Data() const noexcept;

    public:
        const AVPixelFormat PixelFormat;
        const int Width;
        const int Height;
        const size_t Size;

    private:
        FFmpegPointer<uint8_t> m_data;
    }; // class FrameBuffer

} // namespace FE::FFmpeg


#endif //FUNNYEDITOR_SRC_FFMPEG_FRAMEBUFFER_HPP_
