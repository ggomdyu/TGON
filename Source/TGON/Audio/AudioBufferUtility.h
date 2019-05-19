/**
 * @file    AudioBufferUtility.h
 * @author  ggomdyu
 * @since   04/10/2018
 */

#pragma once
#include <cstdint>
#if TGON_PLATFORM_MACOS
#   include <OpenAL/al.h>
#else
#   include <al.h>
#endif

#include "String/StringTraits.h"
#include "String/Hash.h"
#include "Core/Algorithm.h"

#include "AudioBufferType.h"

namespace tgon
{

inline AudioFormat ConvertStringToAudioFormat(const char* audioFormatStr, std::size_t audioFormatStrLen)
{
    char lowercaseStr[32] {};
    BasicStringTraits<char>::ToLower(audioFormatStr, lowercaseStr, std::extent<decltype(lowercaseStr)>::value);

    switch (X65599Hash(lowercaseStr))
    {
    case TGON_X65599("wav"):
        return AudioFormat::Wav;
    case TGON_X65599("ogg"):
        return AudioFormat::OggVorbis;
    case TGON_X65599("mp3"):
        return AudioFormat::Mp3;
    case TGON_X65599("flac"):
        return AudioFormat::Flac;
    case TGON_X65599("m4a"):
        return AudioFormat::M4a;
    case TGON_X65599("opus"):
        return AudioFormat::Opus;
    }

    return AudioFormat::Unknown;
}

template <std::size_t _AudioFormatStrLen>
inline AudioFormat ConvertStringToAudioFormat(const char(&audioFormatStr)[_AudioFormatStrLen])
{
    return ConvertStringToAudioFormat(audioFormatStr, _AudioFormatStrLen - 1);
}

constexpr const char* ConvertAudioFormatToString(AudioFormat AudioFormat)
{
    constexpr const char* audioFormatStringTable[] =
    {
        "",
        "wav",
        "ogg",
        "mp3",
        "flac",
        "m4a",
        "opus",
    };

    return audioFormatStringTable[UnderlyingCast(AudioFormat)];
}

inline ALenum ConvertToALFormat(int32_t channels, int32_t bitsPerSample)
{
    if (channels == 1)
    {
        if (bitsPerSample == 8)
        {
            return AL_FORMAT_MONO8;
        }
        else if (bitsPerSample == 16)
        {
            return AL_FORMAT_MONO16;
        }
    }
    else if (channels == 2)
    {
        if (bitsPerSample == 8)
        {
            return AL_FORMAT_STEREO8;
        }
        else if (bitsPerSample == 16)
        {
            return AL_FORMAT_STEREO16;
        }
    }
    else if (channels == 4)
    {
        return alGetEnumValue("AL_FORMAT_QUAD16");
    }
    else if (channels == 6)
    {
        return alGetEnumValue("AL_FORMAT_51CHN16");
    }

    return 0;
}

} /* namespace tgon */  
