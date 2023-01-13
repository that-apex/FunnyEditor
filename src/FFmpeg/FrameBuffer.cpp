#include "FrameBuffer.hpp"

extern "C"
{
#include <libavutil/imgutils.h>
}

namespace FE::FFmpeg {

    namespace {
        size_t GetBufferSize(AVPixelFormat pixelFormat, int width, int height) {
            int ret = av_image_get_buffer_size(pixelFormat, width, height, 1);
            FFMPEG_CHECK_ERROR(ret, "av_image_get_buffer_size failed");
            return static_cast<size_t>(ret);
        }

        void FreeFrameBuffer(uint8_t *ptr) {
            av_free(static_cast<void *>(ptr));
        }
    }

    FrameBuffer::FrameBuffer(AVPixelFormat pixelFormat, int width, int height) :
            PixelFormat{pixelFormat}, Width{width}, Height{height},
            Size{GetBufferSize(pixelFormat, width, height)},
            m_data{nullptr, &FreeFrameBuffer} {

        auto data = static_cast<uint8_t *>(av_malloc(Size));
        FFMPEG_ASSERT(data, "av_malloc failed");
        m_data.reset(data);
    }

    uint8_t *FrameBuffer::Data() noexcept {
        return m_data.get();
    }

    const uint8_t *FrameBuffer::Data() const noexcept {
        return m_data.get();
    }

} // namespace FE::FFmpeg
