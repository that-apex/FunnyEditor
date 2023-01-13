#pragma once
#ifndef FUNNYEDITOR_SRC_FFMPEG_CODECCONTEXT_HPP_
#define FUNNYEDITOR_SRC_FFMPEG_CODECCONTEXT_HPP_

#include "FFmpeg.hpp"

namespace FE::FFmpeg {

    class Packet; // Packet.hpp
    class Frame; // Frame.hpp

    class CodecContext {
    public:
        explicit CodecContext(AVCodec *codec);

    public:
        [[nodiscard]] AVCodecContext &GetContext() noexcept;

        [[nodiscard]] const AVCodec &GetCodec() noexcept;

        void ParametersToContext(const AVCodecParameters &parameters);

        void Open();

        void SendPacket(Packet &packet);

        bool ReceiveFrame(Frame &frame);

    private:
        FFmpegPointer<AVCodecContext> m_context{nullptr, &ContextDelete};

    private:
        static void ContextDelete(AVCodecContext *context);
    }; // class CodecContext

} // namespace FE::FFmpeg

#endif //FUNNYEDITOR_SRC_FFMPEG_CODECCONTEXT_HPP_
