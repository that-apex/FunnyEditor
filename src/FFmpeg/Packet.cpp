#include "Packet.hpp"

namespace FE::FFmpeg {

    Packet::~Packet() {
        Unref();
    }

    AVPacket &Packet::GetPacket() noexcept {
        return m_packet;
    }

    void Packet::Unref() {
        av_packet_unref(&m_packet);
    }
} // namespace FE::FFmpeg