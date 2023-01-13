#pragma once
#ifndef FUNNYEDITOR_SRC_FFMPEG_FORMATCONTEXT_HPP_
#define FUNNYEDITOR_SRC_FFMPEG_FORMATCONTEXT_HPP_

#include <optional>
#include <vector>
#include "FFmpeg.hpp"
#include "Stream.hpp"

extern "C"
{
#include <libavformat/avformat.h>
}

namespace FE::FFmpeg {

    class Packet; // Packet.hpp

    class FormatContext : NoCopy {
    public:
        FormatContext();

        void Open(std::string_view url);

        void FindStreamInfo();

        Stream& GetStream(size_t index);

        [[nodiscard]] const std::vector<std::unique_ptr<Stream>>& GetStreams();

        [[nodiscard]] Stream* FindStreamByType(StreamType type);

        [[nodiscard]] VideoStream* FindVideoStream();

        [[nodiscard]] AudioStream* FindAudioStream();

        [[nodiscard]] AVFormatContext *GetContext() noexcept;

        void ReadPacket(Packet& packet);

    private:
        FFmpegPointer<AVFormatContext> m_context{nullptr, &ContextDelete};
        std::vector<std::unique_ptr<Stream>> m_streams{};
        bool m_foundStreams{false};

    private:
        static void ContextDelete(AVFormatContext *context);
    }; // class FormatContext

} // namespace FE::FFmpeg

#endif //FUNNYEDITOR_SRC_FFMPEG_FORMATCONTEXT_HPP_
