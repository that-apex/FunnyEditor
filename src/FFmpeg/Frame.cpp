#include "Frame.hpp"

#include "FrameBuffer.hpp"

extern "C"
{
#include <libavutil/imgutils.h>
}

namespace FE::FFmpeg {

    Frame::Frame() {
        AVFrame *frame = av_frame_alloc();
        FFMPEG_ASSERT(frame, "av_frame_alloc failed");

        m_frame.reset(frame);
    }

    AVFrame &Frame::GetFrame() noexcept {
        return *m_frame.get();
    }

    void Frame::FillArrays(const FrameBuffer &buffer) {
        int err = av_image_fill_arrays(m_frame->data, m_frame->linesize, buffer.Data(),
                                       buffer.PixelFormat, buffer.Width, buffer.Height, 1);

        FFMPEG_CHECK_ERROR(err, "av_image_fill_arrays failed");
    }

    void Frame::FrameDelete(AVFrame *frame) {
        av_frame_free(&frame);
    }

} // namespace FE::FFmpeg
