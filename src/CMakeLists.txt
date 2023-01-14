add_library(FunnyEditor_Lib STATIC
        FFmpeg/CodecContext.cpp
        FFmpeg/FFmpeg.cpp
        FFmpeg/FormatContext.cpp
        FFmpeg/Frame.cpp
        FFmpeg/FrameBuffer.cpp
        FFmpeg/Packet.cpp
        FFmpeg/Stream.cpp
        SDL/SDL.cpp
        SDL/Texture.cpp
        SDL/Window.cpp
        Video/Renderer.cpp
        Application.cpp
        Common.cpp
)

target_include_directories(FunnyEditor_Lib
        INTERFACE
            "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(FunnyEditor_Lib
        PUBLIC
            FFmpeg::avfilter
            FFmpeg::avformat
            FFmpeg::avcodec
            FFmpeg::avutil
            FFmpeg::swscale
            ZLIB::ZLIB
            SDL2::SDL2
            easyloggingpp
)

target_compile_definitions(FunnyEditor_Lib
        PRIVATE
           -DSDL_MAIN_HANDLED
)
