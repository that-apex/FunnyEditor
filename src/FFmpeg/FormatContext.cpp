#include "FormatContext.hpp"

#include <algorithm>

#include "Packet.hpp"

namespace FE::FFmpeg {

    FormatContext::FormatContext() {
        m_context.reset(avformat_alloc_context());
    }

    void FormatContext::Open(std::string_view url) {
        AVFormatContext *ctx = m_context.get();
        int err = avformat_open_input(&ctx, url.data(), nullptr, nullptr);

        if (err != 0) {
            m_context.release(); // NOLINT(bugprone-unused-return-value): avformat_open_input frees the context on failure
            throw FFmpegException("avformat_open_input failed", err);
        }
    }

    void FormatContext::FindStreamInfo() {
        int err = avformat_find_stream_info(m_context.get(), nullptr);
        FFMPEG_CHECK_ERROR(err, "avformat_find_stream_info failed");

        m_streams.resize(m_context->nb_streams);

        for (unsigned int i = 0; i < m_context->nb_streams; i++) {
            m_streams[i] = Stream::MakeStream(m_context->streams[i]);
        }

        m_foundStreams = true;
    }

    Stream &FormatContext::GetStream(size_t index) {
        return *GetStreams()[index].get();
    }

    const std::vector<std::unique_ptr<Stream>> &FormatContext::GetStreams() {
        if (!m_foundStreams) {
            FindStreamInfo();
        }

        return m_streams;
    }

    Stream *FormatContext::FindStreamByType(StreamType type) {
        const auto &streams = GetStreams();

        auto found = std::find_if(std::begin(streams), std::end(streams), [type](const auto &stream) -> bool {
            return stream->GetStreamType() == type;
        });

        return found == std::end(streams)
               ? nullptr
               : found->get();
    }

    VideoStream *FormatContext::FindVideoStream() {
        return dynamic_cast<VideoStream *>(FindStreamByType(StreamType::VIDEO));
    }

    AudioStream *FormatContext::FindAudioStream() {
        return dynamic_cast<AudioStream *>(FindStreamByType(StreamType::AUDIO));
    }

    AVFormatContext *FormatContext::GetContext() noexcept {
        return m_context.get();
    }

    void FormatContext::ReadPacket(Packet& packet) {
        int err = av_read_frame(m_context.get(), &packet.GetPacket());
        FFMPEG_CHECK_ERROR(err, "av_read_frame failed");
    }

    void FormatContext::ContextDelete(AVFormatContext *context) {
        avformat_close_input(&context);
    }



} // namespace FE::FFmpeg