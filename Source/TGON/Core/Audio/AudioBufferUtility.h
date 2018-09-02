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

#include "Core/String/StringTraits.h"
#include "Core/Hash/Hash.h"
#include "Core/Utility/Algorithm.h"

#include "AudioBufferType.h"

namespace tgon
{

inline AudioFormat ConvertStringToAudioFormat(const char* audioFormatStr, std::size_t audioFormatStrLen)
{
    char lowercaseStr[32] {};
    StringTraits<char>::ToLower(audioFormatStr, lowercaseStr, std::extent<decltype(lowercaseStr)>::value);

    switch (X65599Hash(lowercaseStr))
    {
    case X65599Hash("wav"):
        return AudioFormat::Wav;
    case X65599Hash("ogg"):
        return AudioFormat::OggVorbis;
    case X65599Hash("mp3"):
        return AudioFormat::Mp3;
    case X65599Hash("flac"):
        return AudioFormat::Flac;
    case X65599Hash("m4a"):
        return AudioFormat::M4a;
    case X65599Hash("opus"):
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
