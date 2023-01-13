#include "FFmpeg.hpp"

#include <sstream>
#include <iomanip>

namespace FE::FFmpeg {

    namespace {
        std::string MakeError(std::string_view prefix, int error) {
            char buf[AV_ERROR_MAX_STRING_SIZE];

            if (av_strerror(error, buf, AV_ERROR_MAX_STRING_SIZE) != 0) {
                strcpy(buf, "av_strerror failed");
            }

            std::stringstream stream;
            stream << prefix << ": " << buf;
            return stream.str();
        }
    }

    FFmpegException::FFmpegException(std::string error) : Exception{std::move(error)} {
    }

    FFmpegException::FFmpegException(std::string_view prefix, int error) : FFmpegException(MakeError(prefix, error)) {
    }


} // namespace FE::FFmpeg
