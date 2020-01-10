/**
 * @file    OggVorbisAudioImporter.h
 * @author  ggomdyu
 * @since   04/20/2018
 */
 
#pragma once
#define STB_VORBIS_HEADER_ONLY
#include <stb_vorbis.c>
#include <gsl/span>

#include "Diagnostics/Debug.h"

#include "AudioImporter.h"

namespace tgon
{

class OggVorbisAudioImporter :
    public AudioImporter
{
/**@section Method */
public:
    static bool IsExactFormat(const gsl::span<const std::byte>& fileData);
    bool Initialize(const gsl::span<const std::byte>& fileData) override;
};

inline bool OggVorbisAudioImporter::Initialize(const gsl::span<const std::byte>& fileData)
{
    if (IsExactFormat(fileData) == false)
    {
        return false;
    }

    // vorbis's each sample is a 16-bit number.
    m_bitsPerSample = 16;

    short* audioData = nullptr;
    auto audioDataBytes = stb_vorbis_decode_memory(reinterpret_cast<const unsigned char*>(fileData.data()), static_cast<int>(fileData.size()), &m_channels, &m_samplingRate, &audioData) * 4;
    m_audioData.reset(reinterpret_cast<std::byte*>(audioData));
    m_audioDataBytes = audioDataBytes;

    return true;
}

inline bool OggVorbisAudioImporter::IsExactFormat(const gsl::span<const std::byte>& fileData)
{
    if (fileData.size() < 16)
    {
        return false;
    }

    return true;
}

} /* namespace tgon */
