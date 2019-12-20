/**
 * @file    OggVorbisAudioImporter.h
 * @author  ggomdyu
 * @since   04/20/2018
 */

#pragma once
#define STB_VORBIS_HEADER_ONLY
#include <stb/stb_vorbis.c>

#include "Diagnostics/Debug.h"

#include "BaseAudioImporter.h"

namespace tgon
{

class OggVorbisAudioImporter :
    public BaseAudioImporter<OggVorbisAudioImporter>
{
/**@section Method */
public:
    static bool IsExactFormat(const std::byte* fileData, size_t fileDataBytes);
    bool Import(const std::byte* fileData, size_t fileDataBytes);
};

inline bool OggVorbisAudioImporter::Import(const std::byte* fileData, size_t fileDataBytes)
{
    if (IsExactFormat(fileData, fileDataBytes) == false)
    {
        return false;
    }

    // vorbis's each sample is a 16-bit number.
    m_bitsPerSample = 16;

    short* audioData = nullptr;
    auto audioDataBytes = stb_vorbis_decode_memory(reinterpret_cast<const unsigned char*>(fileData), static_cast<int>(fileDataBytes), &m_channels, &m_samplingRate, &audioData) * 4;
    m_audioData.reset(reinterpret_cast<std::byte*>(audioData));
    m_audioDataBytes = audioDataBytes;

    return true;
}

inline bool OggVorbisAudioImporter::IsExactFormat(const std::byte* fileData, size_t fileDataBytes)
{
    if (fileDataBytes < 16)
    {
        return false;
    }

    return true;
}

} /* namespace tgon */
