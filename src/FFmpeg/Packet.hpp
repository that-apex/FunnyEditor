#pragma once
#ifndef FUNNYEDITOR_SRC_FFMPEG_PACKET_HPP_
#define FUNNYEDITOR_SRC_FFMPEG_PACKET_HPP_

#include "FFmpeg.hpp"

namespace FE::FFmpeg {

    class Packet : NoCopy {
    public:
        AVPacket& GetPacket() noexcept;

        void Unref();

    private:
        AVPacket m_packet{};

    }; // class Packet

} // namespace FE::FFmpeg


#endif //FUNNYEDITOR_SRC_FFMPEG_PACKET_HPP_
