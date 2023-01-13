#pragma once
#ifndef FUNNYEDITOR_SRC_FFMPEG_FFMPEG_HPP_
#define FUNNYEDITOR_SRC_FFMPEG_FFMPEG_HPP_

#include "../Common.hpp"

extern "C"
{
#include <libavformat/avformat.h>
}

#define FFMPEG_ASSERT(assertion, error) \
    if (!(assertion)) throw FE::FFmpeg::FFmpegException{(error)};

#define FFMPEG_CHECK_ERROR(code, prefix) \
    if ((code) < 0) throw FE::FFmpeg::FFmpegException{(prefix), (code)};

namespace FE::FFmpeg {

    class FFmpegException : public Exception {
    public:
        explicit FFmpegException(std::string error);

        FFmpegException(std::string_view prefix, int error);

    }; // class FFmpegException

    template<typename T>
    using FFmpegDeleter = void (*)(T *);

    template<typename T, typename Deleter =  FFmpegDeleter<T>>
    using FFmpegPointer = std::unique_ptr<T, Deleter>;

}

#endif //FUNNYEDITOR_SRC_FFMPEG_FFMPEG_HPP_
