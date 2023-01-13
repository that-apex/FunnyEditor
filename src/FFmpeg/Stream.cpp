#include "Stream.hpp"

#include "CodecContext.hpp"

namespace FE::FFmpeg {

    AVStream *Stream::GetStream() {
        return m_stream;
    }

    std::unique_ptr<Stream> Stream::MakeStream(AVStream *stream) {
        switch (stream->codecpar->codec_type) {
            case AVMEDIA_TYPE_VIDEO:
                return std::make_unique<VideoStream>(stream);
            case AVMEDIA_TYPE_AUDIO:
                return std::make_unique<AudioStream>(stream);
            default:
                return std::make_unique<UnsupportedStream>(stream);
        }
    }

    const AVCodecParameters &Stream::GetCodecParameters() const noexcept {
        return *m_stream->codecpar;
    }

    double Stream::GetFrameRate() const noexcept {
        AVRational frameRate = m_stream->r_frame_rate;
        return static_cast<double>(frameRate.num) / static_cast<double>(frameRate.den);
    }

    AVCodec *Stream::FindRegisteredDecoder() const noexcept {
        return avcodec_find_decoder(GetCodecParameters().codec_id);
    }

    std::optional<CodecContext> Stream::CreateDecoderContext() const {
        AVCodec *codec = FindRegisteredDecoder();

        return codec == nullptr
               ? std::nullopt
               : std::make_optional<CodecContext>(codec);
    }

    Stream::Stream(AVStream *stream) : m_stream{stream} {
    }

    VideoStream::VideoStream(AVStream *stream) : Stream(stream) {
    }

    StreamType VideoStream::GetStreamType() const noexcept {
        return StreamType::VIDEO;
    }

    AudioStream::AudioStream(AVStream *stream) : Stream(stream) {
    }

    StreamType AudioStream::GetStreamType() const noexcept {
        return StreamType::AUDIO;
    }

    UnsupportedStream::UnsupportedStream(AVStream *stream) : Stream(stream) {
    }

    StreamType UnsupportedStream::GetStreamType() const noexcept {
        return StreamType::UNSUPPORTED;
    }
} // namespace FE::FFmpeg