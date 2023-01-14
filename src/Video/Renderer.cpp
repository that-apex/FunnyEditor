#include "Renderer.hpp"

#include <utility>

namespace FE::Video {


    Renderer::Renderer(SDL::Texture texture, FFmpeg::VideoStream videoStream, FFmpeg::CodecContext decoderContext)
            : m_texture{std::move(texture)}, m_videoStream{std::move(videoStream)},
              m_decoderContext{std::move(decoderContext)}, m_videoStreamIndex{m_videoStream.GetStream()->index},
              m_frame{} {
    }

    bool Renderer::HandlePacket(FFmpeg::Packet &packet) {
        // TODO: This math is wrong
        const double FPS = m_videoStream.GetFrameRate();
        const double DESIRED_PAUSE = 1000.0 / FPS;
        uint32_t start_frame = SDL_GetTicks();

        if (packet.GetPacket().stream_index != m_videoStreamIndex) {
            return false;
        }

        m_decoderContext.SendPacket(packet);

        if (!m_decoderContext.ReceiveFrame(m_frame)) {
            return false;
        }

        m_texture.UpdateYUV(
                nullptr,
                m_frame.GetFrame().data[0], m_frame.GetFrame().linesize[0],
                m_frame.GetFrame().data[1], m_frame.GetFrame().linesize[1],
                m_frame.GetFrame().data[2], m_frame.GetFrame().linesize[2]
        );

        uint32_t real_end_time = SDL_GetTicks();
        uint32_t real_frame_time = real_end_time - start_frame;
        int32_t req_pause = static_cast<int32_t>(DESIRED_PAUSE) - static_cast<int32_t>(real_frame_time);
        if (req_pause > 0) {
            SDL_Delay(req_pause);
        }

        return true;
    }

    SDL::Texture &Renderer::GetTexture() {
        return m_texture;
    }

    Renderer Renderer::Create(SDL::Window &window, FFmpeg::VideoStream videoStream) {
        std::optional<FFmpeg::CodecContext> decoderContext = videoStream.CreateDecoderContext();

        if (!decoderContext) {
            using namespace std::string_literals;

            const char *codecName = avcodec_get_name(videoStream.GetCodecParameters().codec_id);
            throw FFmpeg::FFmpegException("Could not create a decoder for codec "s + codecName);
        }

        decoderContext->ParametersToContext(videoStream.GetCodecParameters());
        decoderContext->Open();

        SDL::Texture texture = window.CreateTexture(
                SDL_PIXELFORMAT_YV12, SDL_TEXTUREACCESS_STATIC,
                decoderContext->GetContext().width, decoderContext->GetContext().height
        );

        return {std::move(texture), std::move(videoStream), std::move(decoderContext).value()};
    }


} // namespace FE::Video