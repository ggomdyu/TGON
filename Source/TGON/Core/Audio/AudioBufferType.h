/**
 * @filename    AudioType.h
 * @author      ggomdyu
 * @since       04/29/2018
 */

#pragma once
#include <al.h>

namespace tgon
{

enum class AudioFormat
{
    Unknown,
    Wav,
    OggVorbis,
    Mp3,
    Flac,
    M4a,
    Opus,
};

enum class AudioSampleFormat
{
    Mono8 = AL_FORMAT_MONO8,
    Mono16 = AL_FORMAT_MONO16,
    Stereo8 = AL_FORMAT_STEREO8,
    Stereo16 = AL_FORMAT_STEREO16,
};

} /* namespace tgon */