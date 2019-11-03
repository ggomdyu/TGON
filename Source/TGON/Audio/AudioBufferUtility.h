/**
 * @file    AudioBufferUtility.h
 * @author  ggomdyu
 * @since   04/10/2018
 */

#pragma once
#include <cstdint>

#include "Text/StringTraits.h"
#include "Text/Hash.h"
#include "Misc/Algorithm.h"

namespace tgon
{

inline AudioFormat ConvertToAudioFormat(const char* str)
{
    char lowercaseStr[32] {};
    BasicStringTraits<char>::ToLower(str, std::strlen(str), lowercaseStr);

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
