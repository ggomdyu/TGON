/**
 * @filename    ImageUtility.h
 * @author      ggomdyu
 * @since       04/10/2018
 */

#pragma once
#include <cstdint>

#include "Core/String/StringTraits.h"
#include "Core/Hash/Hash.h"
#include "Core/Utility/Algorithm.h"

#include "AudioType.h"

namespace tgon
{

inline AudioFormat ConvertStringToAudioFormat(const char* audioFormatStr, std::size_t audioFormatStrLen)
{
    char lowercaseStr[32] {};
    StringTraits<char>::ToLower(audioFormatStr, lowercaseStr);

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
    case X65599Hash("aac"):
        return AudioFormat::Aac;
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
        "aac",
        "opus",
    };

    return audioFormatStringTable[UnderlyingCast(AudioFormat)];
}


} /* namespace tgon */  