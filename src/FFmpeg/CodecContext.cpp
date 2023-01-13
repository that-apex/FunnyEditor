#include "CodecContext.hpp"

#include "Packet.hpp"
#include "Frame.hpp"

namespace FE::FFmpeg {

    CodecContext::CodecContext(AVCodec *codec) {
        AVCodecContext *context = avcodec_alloc_context3(codec);
        FFMPEG_ASSERT(context, "avcodec_alloc_context3 failed");
        m_context.reset(context);
    }

    AVCodecContext &CodecContext::GetContext() noexcept {
        return *m_context.get();
    }

    const AVCodec &CodecContext::GetCodec() noexcept {
        return *m_context.get()->codec;
    }

    void CodecContext::ParametersToContext(const AVCodecParameters &parameters) {
        int ret = avcodec_parameters_to_context(m_context.get(), &parameters);
        FFMPEG_CHECK_ERROR(ret, "avcodec_parameters_to_context failed");
    }

    void CodecContext::Open() {
        int ret = avcodec_open2(m_context.get(), &GetCodec(), nullptr);
        FFMPEG_CHECK_ERROR(ret, "avcodec_open2 failed");
    }

    void CodecContext::SendPacket(Packet& packet) {
        int ret = avcodec_send_packet(m_context.get(), &packet.GetPacket());
        FFMPEG_CHECK_ERROR(ret, "avcodec_send_packet failed");
    }

    bool CodecContext::ReceiveFrame(Frame &frame) {
        int ret = avcodec_receive_frame(m_context.get(), &frame.GetFrame());
        // TODO log

        return ret >= 0;
    }

    void CodecContext::ContextDelete(AVCodecContext *context) {
        avcodec_free_context(&context);
    }
} // namespace FE::FFmpeg
