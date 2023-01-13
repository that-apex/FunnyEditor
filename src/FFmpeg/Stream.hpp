#pragma once
#ifndef FUNNYEDITOR_SRC_FFMPEG_STREAM_HPP_
#define FUNNYEDITOR_SRC_FFMPEG_STREAM_HPP_

#include "FFmpeg.hpp"

namespace FE::FFmpeg {

    class CodecContext; // CodecContext.hpp

    enum class StreamType {
        VIDEO,
        AUDIO,
        UNSUPPORTED
    };

    class Stream{
    public:
        [[nodiscard]] AVStream *GetStream();

        [[nodiscard]] virtual StreamType GetStreamType() const noexcept = 0;

        [[nodiscard]] const AVCodecParameters &GetCodecParameters() const noexcept;

        [[nodiscard]] double GetFrameRate() const noexcept;

        [[nodiscard]] AVCodec *FindRegisteredDecoder() const noexcept;

        [[nodiscard]] std::optional<CodecContext> CreateDecoderContext() const;

    public:
        static std::unique_ptr<Stream> MakeStream(AVStream *stream);

    protected:
        explicit Stream(AVStream *stream);

    protected:
        AVStream *m_stream;

    }; // class Stream

    class VideoStream : public Stream {
    public:
        explicit VideoStream(AVStream *stream);

    public:
        [[nodiscard]] StreamType GetStreamType() const noexcept override;

    }; // class VideoStream

    class AudioStream : public Stream {
    public:
        explicit AudioStream(AVStream *stream);

    public:
        [[nodiscard]] StreamType GetStreamType() const noexcept override;

    }; // class VideoStream

    class UnsupportedStream : public Stream {
    public:
        explicit UnsupportedStream(AVStream *stream);

    public:
        [[nodiscard]] StreamType GetStreamType() const noexcept override;

    }; // class UnsupportedStream

} // namespace FE::FFmpeg

#endif //FUNNYEDITOR_SRC_FFMPEG_STREAM_HPP_
