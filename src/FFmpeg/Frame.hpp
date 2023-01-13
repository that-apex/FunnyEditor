#pragma once
#ifndef FUNNYEDITOR_SRC_FFMPEG_FRAME_HPP_
#define FUNNYEDITOR_SRC_FFMPEG_FRAME_HPP_

#include "FFmpeg.hpp"

namespace FE::FFmpeg {

    class FrameBuffer; // FrameBuffer.hpp

    class Frame : NoCopy {
    public:
        Frame();

        [[nodiscard]] AVFrame &GetFrame() noexcept;

        void FillArrays(const FrameBuffer& buffer);

    private:
        FFmpegPointer<AVFrame> m_frame{nullptr, &FrameDelete};

    private:
        static void FrameDelete(AVFrame *frame);
    }; // class FormatContext

} // namespace FE::FFmpeg


#endif //FUNNYEDITOR_SRC_FFMPEG_FRAME_HPP_
